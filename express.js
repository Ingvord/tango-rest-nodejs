const express = require("express");
const parseRequest = require("./src/js/parse_request").parseRequest;
const processRequest = require("./src/js/process_request");
const app = express();

app.use(express.json());

app.use((req, res, next) => {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Methods", "GET, PUT, PATCH, POST, DELETE");
    res.header("Access-Control-Allow-Headers", "Content-Type");
    next();
});


const port = 10001;

app.get('/tango/attributes', (req, res) => {
    const query = parseRequest(req.query)
    processRequest.processGetRequest(query)
        .then(value => {
            res.send({
                ...query,
                value
            })
        })

})

app.put('/tango/attributes', (req, res) => {
    const body = parseRequest(req.body);
    processRequest.processPutRequest(body).then(value => {
        res.send({
            ...body,
            value
        })
    })
})


app.listen(port, () => {
    console.log(`Start listen on port ${port}`)
})
