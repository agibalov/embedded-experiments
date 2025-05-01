import { useState } from 'react';
import { addNumbers } from './api';
import { Box, Button, TextField, Typography } from '@mui/material';

export default function Calculator() {
    const [numberA, setNumberA] = useState<number>(2);
    const [numberB, setNumberB] = useState<number>(3);

    const [result, setResult] = useState<number | null>(null);

    const addNumbersHandler = async () => {
        try {
            const response = await addNumbers(numberA, numberB);
            setResult(response.result);
        } catch (error) {
            console.error('Error adding numbers:', error);
        }
    };

    return (
        <>
            <Typography variant="h4" component="h1">
                Calculator
            </Typography>

            <Box
                component="form"
                sx={{
                    display: 'flex',
                    flexDirection: 'column',
                    gap: 2,
                    width: 300,
                }}
                noValidate
                autoComplete="off"
                >

                <TextField
                    label="Number A"
                    type="number"
                    variant="standard"
                    value={numberA}
                    onChange={(e) => setNumberA(Number(e.target.value))} />

                <TextField
                    label="Number B"
                    type="number"
                    variant="standard"
                    value={numberB}
                    onChange={(e) => setNumberB(Number(e.target.value))} />

                <TextField
                    label="Result"
                    variant="filled"
                    slotProps={{
                        input: {
                            readOnly: true,
                        },
                    }} 
                    value={result || ""}/>

                <Button variant="contained" onClick={addNumbersHandler}>Add Numbers</Button>
            </Box>
        </>
    );
}