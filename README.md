# E++ Project README

Welcome to the e++ project repository! This project contains a custom integer data type designed to handle arbitrarily large integers and a parser and evaluator for processing arithmetic expressions. The project is implemented in C++ and provides robust tools for high-precision calculations.

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Project Structure](#project-structure)
6. [Examples](#examples)
7. [Contributing](#contributing)
8. [License](#license)

## Introduction

The e++ project introduces a custom integer class `UnlimitedInt` that can handle integers of any size. It also includes a `UnlimitedRational` class for rational numbers, a parser for processing arithmetic expressions, and an evaluator for executing instructions.

## Features

- **UnlimitedInt Class**: A custom integer data type with basic arithmetic operations, capable of representing extremely large integer values.
- **UnlimitedRational Class**: Utilizes `UnlimitedInt` to represent rational numbers with high precision.
- **Parser**: Parses properly bracketed infix expressions, storing variables and their values in a Binary Search Tree (BST) and creating a parse tree.
- **Evaluator**: Reads, parses, and evaluates individual instructions.

## Installation

To set up the project, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/epp.git
    cd epp
    ```

## Usage

To run the e++ evaluator, use the following command:
```sh
./e++
```

The evaluator expects input in the form of properly bracketed infix expressions with no spaces. The assignment operator is represented by `:=`.

## Examples

(terminal) ./e++                      
Enter expressions to evaluate or type 'exit' to quit:
> x:=2    
2/1
> y:=(3*x)
6/1
> z:=((3*y)+(8*x))
34/1
> final:=(z/18)       
17/9
> ending:=(final*999999999999999999999999999999999999999999999999999999999999999999999999999)
1888888888888888888888888888888888888888888888888888888888888888888888888887/1
> exit

