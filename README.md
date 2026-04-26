# SkillSwap System

A console-based peer-to-peer skill exchange platform built in C++ using 
core Object-Oriented Programming principles — no STL used.

Users can register, log in, manage their skill profiles, search for skills 
across other users, and send or receive skill swap requests.

## Features

- User registration and login with duplicate username detection
- Add, view, and remove skills from your profile (up to 15 per user)
- Search for any skill across all registered users
- Send skill swap requests with a custom message to other users
- View and process incoming skill swap requests (accept/reject)
- Tracks total skill searches and failed login attempts via static members
- Preloaded with 5 sample users and skills for immediate testing

## OOP Concepts Demonstrated

| Concept | Where Used |
|---|---|
| Abstract base classes | `Person`, `Request` (pure virtual functions) |
| Inheritance | `User` extends `Person`, `SkillRequest` extends `Request` |
| Composition | `User` owns an array of `Skill` objects |
| Aggregation | `User` holds pointers to `SkillRequest` objects |
| Operator overloading | `==` and `=` overloaded in `Skill` |
| Constructor overloading | `Skill` and `User` have multiple constructors |
| Copy constructor | Defined in `Skill` |
| Static members | `Authentication::loginAttempts`, `SkillManager::total_skills_managed` |
| Friend function | `display_total_skills()` accesses `SkillManager` private data |
| Function overriding | `displayInfo()` overridden in `User` |

## How to Run

**Requirements:** Any C++ compiler (g++, MinGW, MSVC)

```bash
g++ OOP_Project__OEL_.cpp -o skillswap
./skillswap
```

**Sample login credentials (preloaded):**

| Username | Password |
|---|---|
| aima123 | pass123 |
| rania456 | pass456 |
| ahmadl789 | pass789 |
| amjad101 | pass101 |
| emama202 | pass202 |

## Project Structure

Single-file C++ project. Core classes:

- `Person` — abstract base, holds name and email
- `Skill` — stores skill name, description, and level
- `Request` / `SkillRequest` — handles swap request lifecycle
- `User` — full user profile with skills and incoming requests
- `Authentication` — static login/register logic
- `SkillManager` — static skill search across all users
- `RequestManager` — creates and processes requests

## Built With

- C++ (no STL)
- Manual memory management
- Console I/O only

## Author

Fatima Batool — BS Software Engineering, NASTP Institute of Information Technology  
[GitHub](https://github.com/fatimabatool) · [LinkedIn](https://linkedin.com/in/fatimabatool)
