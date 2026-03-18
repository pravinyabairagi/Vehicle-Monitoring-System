# 🚗 Vehicle Monitoring System (Linux System Calls & IPC Project)

## 📌 Overview

This project simulates a **Vehicle Monitoring System** using Linux system calls and POSIX APIs.
It demonstrates how real-time vehicle parameters like speed and seatbelt status are monitored, processed, and logged using processes, threads, and IPC mechanisms.

---

## 🎯 Objective

* To understand and implement Linux system calls
* To demonstrate IPC (Inter-Process Communication)
* To simulate real-time embedded/automotive system behavior
* To build a multi-process and multi-threaded application

---

## ⚙️ Features

* 🚀 Multi-process system using `fork()`
* 🔄 Inter-process communication using `pipe()`
* 🧵 Multi-threading using `pthreads`
* 🔐 Synchronization using `mutex`
* 📡 Signal handling using `signal()`
* 📁 File handling using `open()`, `write()`, `read()`, `lseek()`
* 📊 Random data simulation for speed and seatbelt status
* ⚠️ Warning system for unsafe conditions

---

## 🧠 System Architecture

### 👨‍💻 Processes

* **Parent Process**

  * Controls system
  * Creates child processes
* **Child Process**

  * Generates vehicle data (speed, seatbelt)

---

### 🧵 Threads

* Logging Thread → Writes data into file
* Monitoring Thread → Checks conditions and generates alerts

---

### 🔗 IPC Mechanisms

* **Pipe** → Communication between parent and child
* (Optional: FIFO / Shared Memory for extension)

---

### 🔔 Signal Handling

* `SIGINT (Ctrl + C)` → Graceful shutdown
* Ensures all processes and threads are properly closed

---

### 📂 File Handling

* Log file (`log.txt`) stores:

  * Speed values
  * Seatbelt status
  * Warning messages
* Uses:

  * `open()` → create file
  * `write()` → log data
  * `lseek()` → update file position
  * `close()` → close file

---

## 🔄 Working Flow

1. Parent process starts execution
2. Child process is created using `fork()`
3. Child generates random vehicle data
4. Data is sent to parent using `pipe()`
5. Parent processes data using threads
6. If speed > 20 and seatbelt = OFF → warning generated
7. Data is logged into file
8. On Ctrl + C → system shuts down safely

---

## 🛠️ Technologies Used

* Language: C
* OS: Linux / Ubuntu
* Concepts:

  * System Calls
  * IPC
  * Multithreading
  * Signals

---

## 📦 Project Structure

```
mini_project/
│── main.c
│── speed.c
│── seatbelt.c
│── utils.h
│── Makefile
│── log.txt
│── README.md
```

---

## ▶️ How to Run

### Step 1: Compile

```
make
```

### Step 2: Run

```
make run
```

### Step 3: Clean

```
make clean
```

---

## 📊 Sample Output

```
Speed: 35 km/h | Seatbelt: OFF → WARNING!
Speed: 18 km/h | Seatbelt: ON → SAFE
```

---

## 🧪 Testing

* Normal Run → System works correctly
* Edge Case → High speed without seatbelt triggers warning
* Shutdown → No zombie processes

---

## ⚠️ Future Improvements

* Add GUI dashboard
* Use shared memory
* Add CAN bus simulation
* Real sensor integration

---

## 👨‍🎓 Author

Pravinya Bairagi

---

## 📚 Learning Outcomes

* Practical understanding of Linux system programming
* Hands-on experience with IPC and threading
* Real-world simulation of automotive systems

---
