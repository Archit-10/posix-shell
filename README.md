<h1>POSIX Shell Implementation </h1>

<p>Welcome to my <strong>Custom POSIX Shell</strong> project! This shell isn’t just another terminal interface – it’s built from the ground up, designed to explore the nuances of system calls, error handling, and command-line operations with features that aim to enhance both utility and user experience. Whether you're exploring directory paths or handling process control, this shell has you covered!</p>

<h2><strong>Key Features</strong></h2>
<ul>
    <li><strong>History:</strong> Keeps track of previously executed commands for easy retrieval.</li>
    <li><strong>Autocompletion:</strong> Suggests commands and file paths to improve user experience.</li>
    <li><strong>Signals:</strong> Handles system signals for effective process management.</li>
    <li><strong>pinfo:</strong> Displays information about running processes.</li>
    <li><strong>Background and Foreground Execution:</strong> Supports executing commands in both modes with and without arguments.</li>
    <li><strong>Pipeline:</strong> Allows chaining commands, passing output from one as input to another.</li>
    <li><strong>Redirection:</strong> Supports input and output redirection with pipeline functionality.</li>
</ul>


<h2>Technical Highlights </h2>

<ul>
  <li><strong>Low-Level System Calls</strong>: Implements direct POSIX-compliant system calls like <code>getcwd</code>, <code>chdir</code>, and others, simulating native shell behaviors.</li>
  <li><strong>Error Handling and Validation</strong>: Every function call is designed with extensive error handling, ensuring robust operation even under unexpected conditions.</li>
  <li><strong>Memory Management</strong>: Utilizes efficient memory handling practices to ensure low overhead for better performance.</li>
</ul>

<h2>Built With </h2>

<ul>
  <li><strong>C++</strong>: Core logic and system interactions.</li>
  <li><strong>POSIX APIs</strong>: For seamless, UNIX-compatible system call handling.</li>
  <li><strong>Version Control</strong>: Managed using Git and organized for seamless collaboration.</li>
</ul>

<h2> Architecture Overview </h2>


The shell is designed with a modular architecture separating:

* Core execution engine
* Pipeline handling
* I/O redirection
* Built-in command implementations
* Shell utilities
* Interactive shell features

This separation improves maintainability, extensibility, and debugging efficiency while mirroring the layered design commonly used in production-grade systems software.

---

<h2> Key Features </h2>

<h2> Command Execution</h2>

* Process creation using `fork()`
* Program execution using `execvp()`
* Foreground and background process handling
* Parent-child synchronization using `waitpid()`

<h2> I/O Redirection </h2>

* Input redirection (`<`)
* Output overwrite redirection (`>`)
* Output append redirection (`>>`)
* File descriptor manipulation using `dup2()`

<h2> Pipeline Execution </h2>

* Multi-stage command pipelines using `pipe()`
* Inter-process communication between child processes
* Chained execution of shell commands

<h2> Built-in Commands</h2>

* `cd`
* `pwd`
* `echo`
* `history`
* `pinfo`

<h2> Interactive Shell Features </h2>

* Persistent command history
* Custom shell prompt
* Background process execution (`&`)
* Command parsing and tokenization

---

 <h2> Technologies & Concepts</h2>

| Domain                 | Technologies / Concepts               |
| ---------------------- | ------------------------------------- |
| Language               | C++                                   |
| OS Concepts            | POSIX, UNIX Process Model             |
| Process Management     | `fork()`, `execvp()`, `waitpid()`     |
| IPC                    | `pipe()`                              |
| File Systems           | `open()`, `dup2()`, `close()`         |
| Environment Management | `getenv()`, `setenv()`                |
| Signals                | Signal Handling                       |
| Shell Design           | Parsing, Tokenization, Execution Flow |

---

<h2>Project Structure</h2>

```bash id="sxjlwm"
src/
├── commands/      # Built-in shell commands
├── core/          # Execution engine and pipelines
├── features/      # Shell features and utilities
├── utilities/     # Helper modules and prompt handling
```

---

<h2> Build & Execution</h2> 

## Build

```bash id="ob9e59"
make -f Makefile.mk
```

## Run

```bash id="hsr0lt"
./Posix_Shell
```

---

<h2>Example Usage</h2>

<h2>Standard Commands</h2>

<pre><code>pwd
ls
echo hello world</code></pre>

<h2>Pipeline Execution</h2>

<pre><code>ls | wc -l
cat file.txt | grep main</code></pre>

<h2>I/O Redirection</h2>

<pre><code>echo hello > out.txt
cat < out.txt</code></pre>

<h2>Background Execution</h2>

<pre><code>sleep 10 &</code></pre>

<h2> Challenges Addressed </h2>

* Managing child processes without resource leakage
* Correct handling of file descriptors across pipelines
* Maintaining process synchronization across chained commands
* Avoiding duplicate symbol linkage issues in modular compilation
* Handling shell parsing edge cases for redirection and background execution
* Preserving shell state across directory changes and history persistence

---

<h2> QA </h2>

The shell was manually validated across multiple command execution scenarios, including:

* Foreground and background process execution
* Multi-stage pipelines
* File descriptor redirection correctness
* Built-in command behavior
* Invalid command handling
* Directory traversal edge cases
* Concurrent process execution scenarios

Example validation cases:

```bash id="6b2x2g"
ls | grep cpp
echo hello world | wc
cat file.txt | grep main > out.txt
sleep 5 &
```

---

<h2> Future Scope </h2>

Planned enhancements include:

* Job control (`jobs`, `fg`, `bg`)
* Advanced signal handling
* Multi-command execution using `;`
* Bash-style auto-completion
* Environment variable expansion
* Quote-aware command parsing
* Alias support
* Configuration file support (`.rc`)
* Improved terminal interaction using `readline`
* Process monitoring dashboard

---

<h2>Contributions</h2>
<p> Welcome contributions from the community! If you're interested in contributing, please follow these steps:</p>
<ol>
    <li>Fork the repository.</li>
    <li>Create a new branch for your feature or bug fix.</li>
    <li>Make your changes and commit them with clear messages.</li>
    <li>Push your changes to your forked repository.</li>
    <li>Submit a PR detailing your changes and the motivation behind them.</li>
</ol>
<p>Appreciate your interest in contributing and will review your pull request as soon as possible!</p>

