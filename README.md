# Order Management System in C

Academic project developed for the **Programming Laboratory** course during the 2022/2023 academic year.

The application is a command-line order management system for a furniture company. It was developed in **C** and focuses on structured programming, dynamic memory management, file persistence and modular source-code organization.

> The original coursework was completed as a group assignment. This public portfolio version omits personal information about the other group members and contains a small number of post-submission corrections for stability, portability and presentation, while preserving the original structure and approach of the project.

## Main features

- Customer management: create, search, list, update and remove/deactivate customers.
- Product management: create, search, list, update and remove/deactivate products.
- Material management for product components.
- Order registration for customers and selected products.
- Intended delivery-date handling and delivered/pending order status.
- Binary-file persistence for customers, products, materials and orders.
- Dynamic memory allocation for the main data collections.
- Weekly production report with the materials required for pending deliveries.
- Doxygen-compatible source documentation.

## Project structure

The project intentionally keeps the original NetBeans layout used for the coursework.

```text
LP_G126/
├── main.c
├── clientes.c / clientes.h
├── produtos.c / produtos.h
├── materiais.c / materiais.h
├── encomendas.c / encomendas.h
├── inputs.c / input.h
├── strings.h
├── nbproject/
├── Makefile
├── Doxyfile
└── Tabela_Ficha_Tecnica.csv
```

Runtime `.bin` files, generated documentation, executables and NetBeans private settings are excluded from version control.

## Build

A C11-compatible compiler is sufficient. With GCC, from the project directory:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic clientes.c produtos.c materiais.c encomendas.c inputs.c main.c -o order_management
```

On Windows with MinGW, the output can be named `order_management.exe` instead.

## Run

Linux/macOS:

```bash
./order_management
```

Windows:

```powershell
.\order_management.exe
```

The interface is text-based and written in Portuguese, matching the original academic assignment.

## Persistence

The program uses local binary files for persistence. Existing files are loaded when the application starts, and updated data can be saved through the corresponding menu options. The following runtime files are created locally and intentionally ignored by Git:

- `clientes.bin`
- `produtos.bin`
- `materiais.bin`
- `encomendas.bin`

The application can start without these files; empty in-memory structures are initialized when no persisted data exists.

## Documentation

The source code contains Doxygen comments. If Doxygen is installed, documentation can be generated with:

```bash
doxygen Doxyfile
```

The generated output is written to `documentacao/` and is intentionally not committed because it can be regenerated from the source.

## Academic context

The coursework specification required, among other points, CRUD operations, dynamic memory, file persistence, production-related reporting and modular C code. The repository is kept close to the submitted academic solution rather than being redesigned as a modern production application.

## Author

**Vasco Almeida**
