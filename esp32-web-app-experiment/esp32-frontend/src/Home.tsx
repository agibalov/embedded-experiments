import { useState, useEffect } from "react";
import { getSystemInfo, SystemInfo } from "./api";
import Typography from "@mui/material/Typography";

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
    
    return (
        <Typography>
            <Typography variant="h4" component="h1">
                Home
            </Typography>

            {systemInfo && (<>
                <p>Chip Model: {systemInfo.chipModel}</p>
                <p>Chip Revision: {systemInfo.chipRevision}</p>
                <p>Cores: {systemInfo.cores}</p>
                <p>CPU Frequency: {systemInfo.cpuFrequency}</p>
                <p>Total Heap: {systemInfo.totalHeap}</p>
                <p>Free Heap: {systemInfo.freeHeap}</p>
                <p>SPIFFS Total Bytes: {systemInfo.spiffsTotalBytes}</p>
                <p>SPIFFS Used Bytes: {systemInfo.spiffsUsedBytes}</p>
                <p>SDK Version: {systemInfo.sdkVersion}</p>
                <p>Uptime: {systemInfo.uptime}</p>
                </>
            )}
        </Typography>
    );
}