import React from "react";
import logo from "./logo.svg";
import "./App.css";

import Box from "@mui/material/Box";
import Grid from "@mui/material/Grid";
import { Item } from "./timer.styles";
import { CodeSnippet, InputBox } from "./components";
import { generateSnippet } from "./modules/timer";
import { useState } from "react";

function App() {
  const [configObj, setConfigObj] = useState({});

  function handleChanges(timer: number, frequency: number) {
    const response = generateSnippet(timer, frequency) as any;
    console.log("teste", response);
    setConfigObj(response);
  }

  return (
    <div className="App">
      <header className="App-header"></header>
      <body className="App-body">
        <Grid container spacing={2}>
          <Grid item xs={4}>
            <Item>
              <InputBox onChange={handleChanges}></InputBox>
            </Item>
          </Grid>
          <Grid item xs={4}>
            <Item>
              <CodeSnippet configObj={configObj as any}></CodeSnippet>
            </Item>
          </Grid>
          <Grid item xs={4}>
            <Item>xs=4</Item>
          </Grid>
          <Grid item xs={8}>
            <Item>xs=8</Item>
          </Grid>
        </Grid>
      </body>
    </div>
  );
}

export default App;
