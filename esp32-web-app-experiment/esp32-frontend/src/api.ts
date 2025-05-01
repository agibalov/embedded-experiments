import axios from 'axios';

const api = axios.create({
    baseURL: `${window.location.origin}/api`,
    timeout: 5000
});

export type SystemInfo = {
    message: string;
    chipModel: string;
    chipRevision: number;
    cores: number;
    cpuFrequency: number;
    totalHeap: number;
    freeHeap: number;
    spiffsTotalBytes: number;
    spiffsUsedBytes: number;
    sdkVersion: string;
    uptime: number;
}

export async function getSystemInfo(): Promise<SystemInfo> {
    return await api.get<SystemInfo>('/system').then(response => response.data);
}

export type AddNumbersRequestBody = {
    a: number;
    b: number;
}

export type AddNumbersResponseBody = {
    result: number;
}

export async function addNumbers(a: number, b: number): Promise<AddNumbersResponseBody> {
    return await api.post<AddNumbersResponseBody>('/sum', { a, b }).then(response => response.data);
}
