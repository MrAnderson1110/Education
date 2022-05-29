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

using json_map = std::map<std::string, std::string>;
using key_val = std::pair<std::string, std::string>;

std::string make_json(json_map & map);
json_map load_trains();

int main(int argc, char ** argv) 
{
#ifdef DEBUG
    // json_map test_data;
    // test_data.insert(std::pair<std::string, std::string>("some_train_1", "some_train_time_1"));
    // test_data.insert(std::pair<std::string, std::string>("some_train_2", "some_train_time_2"));
    // test_data.insert(std::pair<std::string, std::string>("some_train_3", "some_train_time_3"));
    // test_data.insert(std::pair<std::string, std::string>("some_train_4", "some_train_time_4"));
    // test_data.insert(std::pair<std::string, std::string>("some_train_5", "some_train_time_5"));
    // test_data.insert(std::pair<std::string, std::string>("some_train_6", "some_train_time_6"));

    // make_json(test_data);
#endif

    try
    {
        cgicc::Cgicc cgi;
        std::cout << cgicc::HTTPContentHeader("application/json") << std::endl;
        auto trains = load_trains();
        auto result = make_json(trains);
        std::cout << result;
    }
    catch (std::exception & e)
    {
        std::cerr << "error while execute cgi script: " << e.what();
        std::cout << cgicc::HTTPStatusHeader(500, e.what()) << std::endl;
    }
}

json_map load_trains()
{
    try 
    {
        const std::string conn_info = "postgresql://train_user:user_pass@127.0.0.1/railroad?connect_timeout=10";

        json_map trains_info;
        pqxx::connection conn(conn_info);
        pqxx::work job(conn);

        auto res = job.exec("SELECT * FROM trains");
        job.commit();

        for (auto const & row : res)
        {
            trains_info.insert(key_val(row[1].as<std::string>(), row[2].as<std::string>()));
        }

        return trains_info;
    }
    catch (std::exception & e)
    {
        std::cerr << "error while execute query: " << e.what();
        throw e;
    }
}

// cmake_minimum_required(VERSION 3.7)
// project(CGI_TEST)

// find_package(cgicc)
// find_package(pqxx)

// add_executable(CGI_TEST main.cpp)

std::string make_json(json_map & map)
{
    const std::string begin_array_token = "[\n";
    const std::string end_array_token = "]\n";
    const std::string begin_block_token = "{\n";
    const std::string end_block_token = "},\n";
    const std::string end_token = ",\n";
    const std::string tab_token = "\t";
    const std::string endl_token = "\n";
    
    std::ostringstream json_stream;

    json_stream << begin_array_token;

    for (auto it = map.begin(); it != --map.end(); ++it)
    {
        json_stream << tab_token << begin_block_token;
        json_stream << tab_token << tab_token << it->first << ": " << it->second << endl_token;
        json_stream << tab_token << end_block_token;
    }

    auto pair = *(--map.end());
    json_stream << tab_token << begin_block_token;
    json_stream << tab_token << tab_token << pair.first << ": " << pair.second << endl_token;
    json_stream << tab_token << "}\n";

    json_stream << end_array_token;

#ifdef DEBUG
    // std::cout << json_stream.str();
#endif

    return json_stream.str();
}