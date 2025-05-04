import { useState, useEffect, useRef } from "react";
import Typography from "@mui/material/Typography";
import Stack from "@mui/material/Stack";
import TextField from "@mui/material/TextField";
import Button from "@mui/material/Button";

export default function Chat() {
    const ws = useRef<WebSocket | null>(null);
    const [message, setMessage] = useState<string>('');
    const [messages, setMessages] = useState<string[]>([]);
  
    useEffect(() => {
      ws.current = new WebSocket(`ws://${window.location.host}:${window.location.port}/ws`);
  
      ws.current.onopen = () => {
        console.log('WebSocket connected');
      };
  
      ws.current.onmessage = (event) => {
        setMessages((prev) => [...prev, event.data].slice(-15));
      };
  
      ws.current.onclose = () => {
        console.log('WebSocket disconnected');
      };
  
      ws.current.onerror = (err) => {
        console.error('WebSocket error:', err);
      };
  
      return () => {
        ws.current?.close();
      };
    }, []);

    function sendMessage() {
        if (!message) {
            return;
        }
        ws.current?.send(message);
        setMessage('');
    }
    
    return (<>
        <Typography variant="h4" component="h1">
            Chat
        </Typography>

        <Stack direction="row" spacing={1} component="form" onSubmit={(e) => e.preventDefault()}>
            <TextField label="Message" variant="outlined" size="small" value={message} onChange={e => setMessage(e.target.value)} />
            <Button variant="contained" type="submit" size="small" onClick={sendMessage}>Send</Button>
        </Stack>

        <ul>
        {messages.map((msg, i) => <li key={i}>{msg}</li>)}
        </ul>
    </>);
}