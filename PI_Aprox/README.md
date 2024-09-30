# PI Approximation
## Description
Approximating PI with a given tolerance. Also shows hex representation of doubles and ULPs.

## Student
Name: Roberto Sprengel Minozzo Tomchak

GRR: 20232369

## How to use
Like most C projects, you can execute the project with the following commands:
```console
  make all
```

```console
  ./main
```

Then write the desired tolerance (must be a positive value).

## Limitations
- Non-positive Tolerance: the given tolerance, since it's a error measurement, must be positive. Negative values don't make sense in this context, and a value of zero requires for infinite iterations to get the exact value of pi;
- Very small Tolerance: values of tolerance smaller than 1e-15 leads to weird behaviour, like infinite loops. This happens because the precision of doubles is around 1e-15, so values smaller han this are impossible/nar impossible to obtain;
- Doubles: the precision of the method is limited to the double variable precision, which in this project uses 8 bytes and the IEEE 754 standard. 

## Calculations

The method works by calculating the next term based on the previous one, and then add to the sum. The calculations are made in a way to minimize computational errors, like prioriting doing multiplications before summations. See calculations.pdf for more.
