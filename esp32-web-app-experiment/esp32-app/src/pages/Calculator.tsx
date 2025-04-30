import { Button, Heading, VStack } from '@chakra-ui/react';
import { useState } from 'react';
import { addNumbers } from '../api';
import { NumberInput, Field } from "@chakra-ui/react"

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
    
    return (<VStack>
        <Heading>Calculator</Heading>

        <Field.Root orientation={"horizontal"}>
          <Field.Label>Number A</Field.Label>
          <NumberInput.Root value={`${numberA}`} onValueChange={(e) => setNumberA(e.valueAsNumber)}>
            <NumberInput.Control />
            <NumberInput.Input />
          </NumberInput.Root>
        </Field.Root>

        <Field.Root orientation={"horizontal"}>
          <Field.Label>Number B</Field.Label>
          <NumberInput.Root value={`${numberB}`} onValueChange={(e) => setNumberB(e.valueAsNumber)}>
            <NumberInput.Control />
            <NumberInput.Input />
          </NumberInput.Root>
        </Field.Root>

        {result !== null && (
            <p>Result: {result}</p>
        )}

        <Button onClick={addNumbersHandler}>Add Numbers</Button>
    </VStack>);
}
