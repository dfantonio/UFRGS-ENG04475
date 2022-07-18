export function calculateMinimumPrescaler(
  baseClock: number,
  desiredFrequency: number
) {
  const basePeriod = 1 / (baseClock / 4);
  const desiredPeriod = 1 / desiredFrequency;
  const maxCount = Math.pow(2, 8);

  for (let pow = 1; pow <= 8; pow++) {
    const amountOfCounts = desiredPeriod / basePeriod / Math.pow(2, pow);

    if (amountOfCounts < maxCount) {
      return {
        prescaler: Math.pow(2, pow),
        count: maxCount - Math.round(amountOfCounts),
      };
    }
  }
  return { prescaler: 2, count: 1 };
}
