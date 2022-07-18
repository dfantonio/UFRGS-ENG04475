import { calculateMinimumPrescaler } from "./prescaler";
import { setPrescaler } from "./registers";

export function generateTimer0Params(frequency: number) {
  // T0IF é a flag de estouro

  const decimalPrescaler = calculateMinimumPrescaler(2000000, frequency);
  return {
    OPTION_REG: setPrescaler(decimalPrescaler.prescaler),
    TMR0: String(decimalPrescaler.count),
  };
}
