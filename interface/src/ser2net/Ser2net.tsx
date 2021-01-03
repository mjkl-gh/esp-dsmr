import React, { Component } from 'react';
import { Redirect, Switch, RouteComponentProps } from 'react-router-dom'

import { Tabs, Tab } from '@material-ui/core';

import { AuthenticatedContextProps, withAuthenticatedContext, AuthenticatedRoute } from '../authentication';
import { MenuAppBar } from '../components';
import Ser2netStatusController from './Ser2netStatusController';

type Ser2netProps = AuthenticatedContextProps & RouteComponentProps;

class Ser2net extends Component<Ser2netProps> {

  handleTabChange = (event: React.ChangeEvent<{}>, path: string) => {
    this.props.history.push(path);
  };

  render() {
    const { authenticatedContext } = this.props;
    return (
      <MenuAppBar sectionTitle="SER2NET">
        <Tabs value={this.props.match.url} onChange={this.handleTabChange} variant="fullWidth">
          <Tab value="/ser2net/status" label="SER2NET Status" />
        </Tabs>
        <Switch>
          <AuthenticatedRoute exact path="/ser2net/status" component={Ser2netStatusController} />
          <Redirect to="/ser2net/status" />
        </Switch>
      </MenuAppBar>
    )
  }
}

export default withAuthenticatedContext(Ser2net);
