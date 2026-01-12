# React List State Management

## Overview

This project is a solution to a technical assessment focused on evaluating core frontend skills using **React** and **TypeScript**, with emphasis on **state management**, **user interaction**, and **code clarity** rather than visual design.

The exercise consists of implementing a small interactive list where users can add and remove items, demonstrating fundamental React patterns and clean component logic.

---

## Technical Test Context

**Role:** Senior Software TypeScript Developer (React & Node.js)  
**Scope:** Frontend (React)  
**Time Constraint:** 40 minutes  
**Focus:** Functionality, usability, and code quality

---

## Problem Statement

Implement a React application that:

- Provides a text input and a button to add elements to a list
- Appends the input value to the list when the button is clicked
- Removes an element from the list when it is clicked
- Prioritizes functionality and usability over visual design
- Is fully implemented using **TypeScript**

---

## Solution Approach

The solution focuses on simplicity and clarity:

- Local state is managed through a custom React hook (`useItems`)
- Uncontrolled input handled via form submission and DOM access
- Event handlers are clearly separated for:
  - Adding new items
  - Removing existing items
- Immutable state updates are applied to ensure predictable behavior

No external state management libraries are used, as the problem scope does not justify additional abstraction.

---

## Architecture Notes

- Business logic is encapsulated in custom hooks:
  - `useItems` handles list state and mutations
  - `useSEO` manages document metadata as a side effect
- Presentational components remain stateless and focused on UI

---

## What This Project Demonstrates

- Correct use of **React hooks** for state management
- Clean and predictable state updates
- Proper handling of user interactions and events
- Type-safe implementation using **TypeScript**
- Clear separation of concerns within a small React component
- Ability to deliver a complete, functional solution within a constrained timeframe

---

## Technologies Used

- React
- TypeScript
- Vite
- Node.js
- npm

---

## Requirements

- Node.js >= 22
- npm >= 10

---

## Setup & Execution

Install dependencies:

```bash
npm install
```

Run the development server:

```bash
npm run dev
```

The application will be available at:

```bash
http://localhost:5173
```

---

## Notes

- The project avoids unnecessary third-party abstractions while using lightweight custom hooks where they improve clarity and separation of concerns
- Styling is kept minimal to focus on behavior and usability.
- This repository is part of a broader Dev Lab workspace, where each project serves a clear technical or evaluative purpose.

---
