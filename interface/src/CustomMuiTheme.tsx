import React, { Component } from 'react';

import { CssBaseline } from '@material-ui/core';
import { MuiThemeProvider, createMuiTheme, StylesProvider } from '@material-ui/core/styles';
import * as colors from '@material-ui/core/colors';

const theme = createMuiTheme({
  palette: {
    type:"dark",
    primary: {
      main: colors.grey[900]
    },
    secondary: {
      main: '#CE93D8'
    },
    info: {
      main: colors.blueGrey[900]
    },
    warning: {
      main: colors.orange[500]
    },
    error: {
      main: colors.red[500]
    },
    success: {
      main: colors.green[500]
    }
  }
});

export default class CustomMuiTheme extends Component {

  render() {
    return (
      <StylesProvider>
        <MuiThemeProvider theme={theme}>
          <CssBaseline />
          {this.props.children}
        </MuiThemeProvider>
      </StylesProvider>
    );
  }

}
