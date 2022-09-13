# Pid to pdg module

Simple kernel module, tested under 5.15.0-47-generic, to obtain the pgd address of a process given its pid.

## Usage
```
:/proc# echo '1' > pid_to_pgd 
:/proc# cat pid_to_pgd 
    000000004dc7c3bd

```