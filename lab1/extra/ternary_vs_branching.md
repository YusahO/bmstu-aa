<style>
    pre {
        white-space: pre-wrap;
    }
</style>


<table>
<table>
    <tr>
        <th> C++ код </th>
        <th> Дизассемблированный код  </th>
    </tr>
    <tr>
        <td>
            <pre>
const char \*a = "hello";
const char \*b = "hi";
int main()
{
    int res = (a[1] != b[1]);
}
            </pre>
        </td>
        <td>
            <pre>
main:
    push    rbp
    mov     rbp, rsp
    mov     rax, qword ptr [rip + a]
    movsx   eax, byte ptr [rax + 1]
    mov     rcx, qword ptr [rip + b]
    movsx   ecx, byte ptr [rcx + 1]
    cmp     eax, ecx
    setne   al
    and     al, 1
    movzx   eax, al
    mov     dword ptr [rbp - 4], eax
    xor     eax, eax
    pop     rbp
    ret
            </pre>
        </td>
    </tr>
    <tr>
        <td>
            <pre>
const char \*a = "hello";
const char \*b = "hi";
int main()
{
    int res = (a[1] == b[1]) ? 0 : 1;
}
            </pre>
        </td>
        <td>
            <pre>
main:
    push    rbp
    mov     rbp, rsp
    mov     rax, qword ptr [rip + a]
    movsx   edx, byte ptr [rax + 1]
    mov     rax, qword ptr [rip + b]
    movsx   esi, byte ptr [rax + 1]
    mov     eax, 1
    xor     ecx, ecx
    cmp     edx, esi
    cmove   eax, ecx
    mov     dword ptr [rbp - 4], eax
    xor     eax, eax
    pop     rbp
    ret
            </pre>
        </td>
    </tr>
    <tr>
        <td>
            <pre>
const char \*a = "hello";
const char \*b = "hi";
int main()
{
    int res;
    if (a[1] == b[1])
        res = 0;
    else
        res = 1;
}
            </pre>
        </td>
        <td>
            <pre>
main:
    push    rbp
    mov     rbp, rsp
    mov     dword ptr [rbp - 4], 0
    mov     rax, qword ptr [rip + a]
    movsx   eax, byte ptr [rax + 1]
    mov     rcx, qword ptr [rip + b]
    movsx   ecx, byte ptr [rcx + 1]
    cmp     eax, ecx
    jne     .LBB0_2
    mov     dword ptr [rbp - 8], 0
    jmp     .LBB0_3
.LBB0_2:
    mov     dword ptr [rbp - 8], 1
.LBB0_3:
    mov     eax, dword ptr [rbp - 4]
    pop     rbp
    ret
            </pre>
        </td>
    </tr>
</table>