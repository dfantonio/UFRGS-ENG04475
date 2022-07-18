import {
  FormControl,
  InputAdornment,
  InputLabel,
  MenuItem,
  Select,
  TextField,
} from "@mui/material";
import { useEffect, useState } from "react";
import { Form } from "./inputBox.style";

type InputBoxProps = {
  onChange: (timer: number, frequency: number) => void;
};

export const InputBox = ({ onChange }: InputBoxProps) => {
  const [timer, setTimer] = useState(0);
  const [frequency, setFrequency] = useState(0);

  useEffect(() => {
    if (frequency > 0) onChange(timer, frequency);
    console.log("aaaa");
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [frequency, timer]);

  return (
    <Form>
      <FormControl fullWidth>
        <InputLabel id="demo-simple-select-label">Timer</InputLabel>
        <Select
          labelId="demo-simple-select-label"
          id="demo-simple-select"
          value={timer}
          label="Timer"
          onChange={(value) => setTimer(Number(value.target.value))}
        >
          <MenuItem value={0}>Timer 0</MenuItem>
          <MenuItem value={1}>Timer 1</MenuItem>
          <MenuItem value={2}>Timer 2</MenuItem>
        </Select>
      </FormControl>
      <TextField
        id="outlined-basic"
        label="Frequência"
        type="number"
        placeholder="100"
        variant="outlined"
        onChange={(value) => setFrequency(Number(value.target.value))}
        InputProps={{
          endAdornment: <InputAdornment position="end">Hz</InputAdornment>,
        }}
      />
    </Form>
  );
};
