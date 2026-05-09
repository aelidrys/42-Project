<h1>Transcendence</h1>

<h2>Project Overview</h2>
<h4>Transcendence is a website of ping pong game with possibility of create users and play remote/local games and tournaments, store matches of games and tournaments in data base.</h4>
<h2>Project Tech Stack</h2>
<h4>In this project we use, Django in Backend and JS,HTML,CSS in Frontend and Postgresql as databas</h4>

---
#### Represintation of relationships in a UML Diagram
<img src="https://d2slcw3kip6qmk.cloudfront.net/marketing/blog/2017Q3/er-diagram-symbols-and-notation/ERDCardinallity.png" width=400px height=400px></img>

<h3>Database schema</h3>
<img src="Tournament/database_schema.png"></img>

---

## Run App
- add a file named `.env` with this content bellow:
``` sql
SECRET_KEY=44edyh*y=h(yl0!*ru@)^yu9_+9^gb0!$g4!*426%eyye@#w0q

# DB
POSTGRES_NAME=postgsql
POSTGRES_DB=postgsql
POSTGRES_USER=postgres
POSTGRES_PASSWORD=postgres
POSTGRES_PORT=5432
```

- run `make`
- go to `localhost:8082`
