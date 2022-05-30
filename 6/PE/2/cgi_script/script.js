const url="railroads.cgi";
function loadSelector() {
    $.getJSON(url, (data, status) => {
        const select = $("#selector");
        for(i in data)
        {
            const option = $(document.createElement("option"));
            option.text(data[i]["name"]);
            option.val(data[i]["id"]);
            select.append(option);
        }
    });
}

function redraw(schedule) {
    $("#tab").fadeOut(30, () => {
        $("#body").children("tr").remove();

        for (i in schedule) {
            const row = document.createElement("tr");
            if (i % 2) {
                row.setAttribute("class", "entity odd");
            } else {
                row.setAttribute("class", "entity even");
            }

            const name = document.createElement("td");
            name.innerText = schedule[i].name;
            row.appendChild(name);

            const time = document.createElement("td");
            time.innerText = schedule[i].time;
            row.appendChild(time);

            $("#body").append(row);
        }

        $("#tab").fadeIn();
    })
}

function onSelect() {
    const selection = $("#selector").val();
    let query = url;
    if (selection != 0) {
        query = url + "?select=" + selection;
    }

    $.getJSON(query, (data, status) => {
        if (status != "success") {
            return;
        }

        schedule = [];

        for (i in data) {
            console.warn("on select data length:", data.length);
            schedule.push({
                id: data[i].id,
                name: data[i].name,
                time: data[i].time
            });
        }

        redraw(schedule);
    });
}

$(document).ready(function(){
    $("#selector").change(() => { onSelect() });
    loadSelector();
    onSelect();
});