import { Heading, VStack } from '@chakra-ui/react';
import { useEffect, useState } from 'react';
import { ProgressCircle } from "@chakra-ui/react"
import { getSystemInfo, SystemInfo } from '../api';

export default function Home() {
    const [systemInfo, setSystemInfo] = useState<SystemInfo | null>(null);

    useEffect(() => {
        getSystemInfo()
            .then(systemInfo => {
                setSystemInfo(systemInfo);
            })
            .catch(error => {
                console.error('Error fetching data:', error);
            });
    }, []);
    
    return (<VStack>
        <Heading>Home Page</Heading>
        {!systemInfo ?
            <>
                <ProgressCircle.Root value={null} size="sm">
                    <ProgressCircle.Circle>
                        <ProgressCircle.Track />
                        <ProgressCircle.Range />
                    </ProgressCircle.Circle>
                </ProgressCircle.Root>
            </>
        :
            <>
                <p>Chip Model: {systemInfo.chipModel}</p>
                <p>Chip Revision: {systemInfo.chipRevision}</p>
                <p>Cores: {systemInfo.cores}</p>
                <p>CPU Frequency: {systemInfo.cpuFrequency} MHz</p>
                <p>Total Heap: {systemInfo.totalHeap} bytes</p>
                <p>Free Heap: {systemInfo.freeHeap} bytes</p>
                <p>SPIFFS Total Bytes: {systemInfo.spiffsTotalBytes} bytes</p>
                <p>SPIFFS Used Bytes: {systemInfo.spiffsUsedBytes} bytes</p>
                <p>SDK Version: {systemInfo.sdkVersion}</p>
                <p>Uptime: {systemInfo.uptime} ms</p>
            </>
        }
    </VStack>);
}
