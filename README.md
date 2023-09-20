<!DOCTYPE html>
<html>
<head>
</head>
<body>
    <h1>Minishell Project</h1>
    <h2>Project Overview</h2>
    <p>The Minishell project is an implementation of a Unix-like shell. This project is part of the curriculum at 42 Seoul.</p>
    <h2>Features</h2>
    <ul>
        <li>Accepts user input and processes executable commands.</li>
        <li>Supports built-in shell commands (cd, echo, export, unset, env, etc.).</li>
        <li>Handles environment variables.</li>
        <li>Supports basic shell features such as pipes (|), redirection (<, >), etc.</li>
        <li>Signal handling (Ctrl+C, Ctrl+D, etc.).</li>
    </ul>
    <h2>Usage</h2>
    <ol>
        <li>Clone this repository:</li>
        <pre><code>git clone https://github.com/JEGHTNER/minishell.git</code></pre>
        <li>Navigate to the project folder:</li>
        <pre><code>cd minishell</code></pre>
        <li>Compile the project:</li>
        <pre><code>make</code></pre>
        <li>Run Minishell:</li>
        <pre><code>./minishell</code></pre>
        <li>You can now use Minishell for executing commands.</li>
    </ol>
    <h2>Example</h2>
    <pre><code>
$ ./minishell
minishell> ls -l
# The result of the 'ls -l' command is displayed.
minishell> cd /path/to/directory
# Change the directory.
    </code></pre>
    
</body>
</html>
