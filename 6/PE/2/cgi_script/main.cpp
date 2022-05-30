// cgicc
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPContentHeader.h>
#include <cgicc/HTTPStatusHeader.h>

// std
#include <sstream>
#include <iostream>
#include <map>

//pqxx
#include <pqxx/pqxx>

struct Train_info;

using train_info_vec = std::vector<Train_info>;

std::string make_json(train_info_vec &);
train_info_vec load_trains(int);
int parceQuery(cgicc::Cgicc &);

int main(int argc, char ** argv) 
{
    try
    {
        cgicc::Cgicc cgi;
        std::cout << cgicc::HTTPContentHeader("application/json") << std::endl;
        auto selection = parceQuery(cgi);
        auto trains = load_trains(selection);
        auto result = make_json(trains);
        std::cout << result;
    }
    catch (std::exception & e)
    {
        std::cerr << "error while execute cgi script: " << e.what();
        std::cout << cgicc::HTTPStatusHeader(500, e.what()) << std::endl;
    }
}

struct Train_info
{
    int id;
    std::string name;
    std::string time;
};

int parceQuery(cgicc::Cgicc & cgi)
{
    int selection = -1;
    cgicc::form_iterator id = cgi.getElement("select");
    if (id != cgi.getElements().end())
    {
        selection = id->getIntegerValue(0);
    }

    return selection;
}

train_info_vec load_trains(int selection)
{
    try 
    {
        const std::string conn_info = "postgresql://train_user:user_pass@127.0.0.1/railroad?connect_timeout=10";

        train_info_vec trains_info;
        pqxx::connection conn(conn_info);
        pqxx::work job(conn);

        auto res = job.exec("SELECT * FROM trains");
        job.commit();

        std::cerr << "filtered id:" << selection;

        for (auto const & row : res)
        {
            int id = row[0].as<int>();
            if (selection >= 0 && id != selection) {
                continue;
            }
            
            Train_info ti = {
                id,
                row[1].as<std::string>(),
                row[2].as<std::string>()
            };
            trains_info.push_back(ti);
        }

        return trains_info;
    }
    catch (std::exception & e)
    {
        std::cerr << "error while execute query: " << e.what();
        throw e;
    }
}

std::string make_json(train_info_vec & v)
{
    const std::string begin_array_token = "[\n";
    const std::string end_array_token = "]\n";
    
    std::ostringstream json_stream;

    json_stream << begin_array_token;
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        json_stream << "\t{\n";
        json_stream << "\t\t\"id\":\"" << it->id << "\",\n";
        json_stream << "\t\t\"name\":\"" << it->name << "\",\n";
        json_stream << "\t\t\"time\":\"" << it->time << "\"\n";

        if (it == --v.end())
        {
            json_stream << "\t}\n";
        }
        else
        {
            json_stream << "\t},\n";
        }
    }
    json_stream << end_array_token;

    return json_stream.str();
}