# Level00 — Binary Analysis & Exploitation

## Context

Inside the home directory of the `level00` user, we find a binary named `level00`.
The program requests a password, and if the condition is satisfied, it spawns a shell.
Our objective is to determine the correct password and obtain shell access with escalated privileges.

---

## Initial Environment — Directory Listing

```bash
$ ls -la
total 13
dr-xr-x---+ 1 level01 level01   60 Sep 13  2016 .
dr-x--x--x  1 root    root     260 Oct  2  2016 ..
-rw-r--r--  1 level01 level01  220 Sep 10  2016 .bash_logout
lrwxrwxrwx  1 root    root       7 Sep 13  2016 .bash_profile -> .bashrc
-rw-r--r--  1 level00 level00 3533 Sep 10  2016 .bashrc
-rwsr-s---+ 1 level01 users   7280 Sep 10  2016 level00
-rw-r--r--  1 level01 level01  675 Sep 10  2016 .profile
```

> **Note:** the binary `level00` has the **SUID** bit set (`rws`), so it runs with the privileges of its owner (`level01`).

---

## Running the Binary

```bash
$ ./level00
***********************************
*            -Level00 -           *
***********************************
Password:
```

Entering a random value yields:

```bash
Password:1234
Invalid Password!
```

The program validates the entered value against a hidden constant.

---

## Static Analysis (Decompilation)

Decompiling the binary reveals the following simplified logic:

```c
int main(int argc, const char **argv)
{
  int password;
  puts("***********************************");
  puts("* \t     -Level00 -\t\t  *");
  puts("***********************************");
  printf("Password:");
  scanf("%d", &password);
  if ( password == 5276 )
  {
    puts("\nAuthenticated!");
    system("/bin/sh");   // <-- spawn a shell
    return 0;
  }
  else
  {
    puts("\nInvalid Password!");
    return 1;
  }
}
```

**Key points:**

* Input is read with `scanf("%d", &password)` → treated as an integer.
* The expected password is the constant `5276`.
* On match, the program executes `system("/bin/sh")`, giving a shell with `level01` privileges.

---

## Assembly Verification

Relevant disassembly snippet:

```asm
0x080484e3 <+79>:    mov    eax,DWORD PTR [esp+0x1c]
0x080484e7 <+83>:    cmp    eax,0x149c     ; compare with 0x149c
0x080484ec <+88>:    jne    0x804850d      ; jump if not equal
```

`0x149c` (hex) = **5276** (decimal). This confirms the required password.

---

## Exploitation

Provide the correct password to obtain a shell:

```bash
$ ./level00
***********************************
*            -Level00 -           *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```

**Result:** a shell as `level01` and retrieval of the next-level password

