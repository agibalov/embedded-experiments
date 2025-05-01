import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

// https://vite.dev/config/
export default defineConfig({
  plugins: [react(), dummyRestApi()],
})

function dummyRestApi() {
  return {
    name: 'dummy-rest-api',
    configureServer(server: any) {
      server.middlewares.use('/api/system', (req: any, res: any, next: any) => {
        if (req.method === 'GET') {
          res.setHeader('Content-Type', 'application/json');
          res.end(JSON.stringify({
            "chipModel": "DUMMY-9000",
            "chipRevision": 3,
            "cores": 2,
            "cpuFrequency": 240,
            "totalHeap": 318312,
            "freeHeap": 218340,
            "spiffsTotalBytes": 1318001,
            "spiffsUsedBytes": 584328,
            "sdkVersion": "v4.4.7-dirty",
            "uptime": 12345
          }));
        } else {
          next();
        }
      });

      server.middlewares.use('/api/sum', (req: any, res: any, next: any) => {
        if (req.method === 'POST') {

          let bodyString = '';
          req.on('data', (chunk: any) => {
            bodyString += chunk.toString();
          });

          req.on('end', () => {
            const body = JSON.parse(bodyString);
            res.setHeader('Content-Type', 'application/json');
            res.end(JSON.stringify({
              "result": 100 * (body.a + body.b)
            }));
          });
        } else {
          next();
        }
      });
    },
  }
}