import { generateTimer0Params } from "./timer0";

export function generateSnippet(timer: number, frequency: number) {
  switch (timer) {
    case 0:
      return generateTimer0Params(frequency);

    default:
      break;
  }
}
