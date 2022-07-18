/**
 * Podemos fazer assim pois os bits do prescaler são os 3 mais a direita e o valor só vai até 7
 */
export function setPrescaler(decimalValue: number) {
  const hexValue = Math.log2(decimalValue) - 2; //TODO: Corrigir esse bug
  return `0x0${hexValue}`;
}
