import { FC } from 'react';

import { Typography } from '@mui/material';

import { SectionContent } from '../components';

const DemoInformation: FC = () => (
  <SectionContent title='Demo Information' titleGutter>
    <Typography variant="body1" paragraph>
      To be released at a later point
    </Typography>
  </SectionContent>
);

export default DemoInformation;
