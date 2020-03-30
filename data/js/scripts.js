function displayParametersContent() {
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {
        if (this.readyState === 4 && this.status === 200) {
            let content = '';
            content += "<form style='height: calc(100vh - 3em);overflow-y: auto;' method='post' action='/submit_form_parameters'>";
            this.response.forEach(function (parameter) {
                content += "<div class='group'>";
                content += "   <input type='text' required='true' value=" + parameter.value + " name=" + parameter.key + " >";
                content += "    <span class='highlight'></span>";
                content += "    <span class='bar'></span>";
                content += "    <label>" + parameter.key + " (" + parameter.unit + ")</label>";
                content += "</div>";
            });
            content += "<div style='display: flex; flex-direction: column; align-items: flex-end; margin: 1em;'>";
            content += "    <button class='btn btn-form' type='submit'><span>Enregistrer</span></button>";
            content += "</div>";
            content += "</form>";
            document.getElementById('content').innerHTML = content;
        }
    };

    xhttp.open("GET", "getParameters", true);
    xhttp.send();


}

function displayContent() {
    // if (window.location.endsWith('parameters')) {
    displayParametersContent(content);
//    }
}
