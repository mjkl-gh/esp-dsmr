import { FC } from 'react';

import { List } from '@mui/material';
import DashboardIcon from '@mui/icons-material/Dashboard';

import { PROJECT_PATH } from '../api/env';
import LayoutMenuItem from '../components/layout/LayoutMenuItem';

const ProjectMenu: FC = () => (
  <List>
    <LayoutMenuItem icon={DashboardIcon} label="Dashboard" to={`/${PROJECT_PATH}/demo`} />
  </List>
);

export default ProjectMenu;
