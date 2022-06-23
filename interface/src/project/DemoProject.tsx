
import React, { FC } from 'react';
import { Navigate, Route, Routes } from 'react-router-dom';

import { Tab } from '@mui/material';

import { RouterTabs, useRouterTab, useLayoutTitle } from '../components';

import DemoInformation from './DemoInformation';

const DemoProject: FC = () => {
  useLayoutTitle("Demo Project");
  const { routerTab } = useRouterTab();

  return (
    <>
      <RouterTabs value={routerTab}>
        <Tab value="information" label="Information" />
      </RouterTabs>
      <Routes>
        <Route path="information" element={<DemoInformation />} />
        <Route path="/*" element={<Navigate replace to="information" />} />
      </Routes>
    </>
  );
};

export default DemoProject;
