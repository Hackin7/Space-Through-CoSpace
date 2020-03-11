# CoSpace Rescue Tutorial

1: Getting Started

CoSpace Rescue is a virtual robot competition, where virtual robots you code in C/C++ compete to get the most points in a virtual simulation.

[https://www.cospacerobot.org/](https://www.cospacerobot.org/)

There are competitions about this software. The main competition using this software is Robocup Junior Rescue Simulation. For now you can check more about the rules here: [https://www.cospacerobot.org/competition/cospace-rescue](https://www.cospacerobot.org/competition/cospace-rescue)

In this tutorial, you are going to learn how to install & compile code to run on the virtual robot in Cospace Rescue Simulator.

This tutorial series assumes knowledge of programming, and more specifically C++ programming. If you know how to program in other languages, chances are you just need to learn the C++ syntax. However, if you don’t know how to program, you should probably program in other languages first, like Python.

## Download & Install

You can download the files from here: [https://www.cospacerobot.org/download/cospace-rescue-download](https://www.cospacerobot.org/download/cospace-rescue-download)

![](https://lh5.googleusercontent.com/VvUWTnHt0DiJf6ZPh7stciIVilI0HUMsmxgFLID0XO1-pDqxM17HzI_CWwi7K_sqwk9orHWXBMw2cas6QOSyPkgmJKddoVOaQnx8QaRB5EhVLu0na3AM0Cys_Pa6jZJWw328JXWz)

![](https://lh4.googleusercontent.com/OMX4Pbr0K3Q1pYUbvOS8d665t3inSmPmO6fX-lcPC-YtLwBE8JzT6RskaCJvBSpiF_LxLnjtAoJh3HMSxUQQebopdov1PwHLQsSotcF454_jtCQGeGDYUaQS7zF4BLrTgc4alwst)

  

You may need to get a serial code to use all of Cospace Rescue’s features, however, even without a serial code, you should still be able to use the software to compile & run code. It’s just that you would not have manual relocation of the robot along with some other features.

  

When you are done you should be able to get a screen like this. The difference in the map does not matter.

![](https://lh3.googleusercontent.com/fqGLOZ4oJcKewbLKi77ajtU0voooFTf_N_8J_SQ6uoZyxIJtTPbIS61Z7DKPnmufJjyaMUGmPNip3mDZfOr2wTr0F753eQPGUAjwRG2982q_le51Vw2Xodhnjjz_8IYwFI2ACOo9)

## Using C

Let’s start by compiling for C, shall we? Click the AI button. You should get this window

![](https://lh5.googleusercontent.com/SRrsPS9Z3bforhk6g3oqwy2Wxvszl3dDhBTp6fvuCUNdmgOU12C50hkah6wk8LkEs4fxv4NdhB-Yc0GQVuAVCYmhpfEExGs7x9kC-1RhFL6ieoAlhPhxjwqUsD_KkOCSl-NA-0V1)

To get code for C click the build project icon in the menu. Create your project, and in that new folder, ai.c should be generated. Only ai.c is needed

![](https://docs.google.com/drawings/u/0/d/s52kGbcESjWgcNO56RdvTrg/image?w=223&h=114&rev=7&ac=1&parent=1RpODTs_ukJqa39zscydEmW6fmhVRyLtL4GC0di6UGzM)![](https://lh4.googleusercontent.com/fKGumMJxgdQhuDLZuejnIhNN4KW3SljYZY81x8M8UK2HpkyeIPvxfXynGHh7zVOG0Lc_YBa96A0KSTLJXUhziV0BDxV_ETt28EhL8x1wXvnXrMoCwfVFHaHtd0aZedwjaCcbc9_6)

![](https://lh6.googleusercontent.com/kqvO7y8nX9Zgt6xRfTqaSu0EbSCGuXaXU1GxBdk3CTg8o3N9a5EVcAXhtz2Gcgi7xa--p5znYTSNfeg2YVFQHe6tpthpN_Nk5AeUFFbLdVXH2F1rudG-r8G8n3LpVP_1aOpVH45u)

  

To compile the code click the Upload to Robot icon in the main menu. Select your file and then compile

![](https://docs.google.com/drawings/u/0/d/s8i9aqys_7-fDeLfBZrJFOg/image?w=266&h=136&rev=3&ac=1&parent=1RpODTs_ukJqa39zscydEmW6fmhVRyLtL4GC0di6UGzM)

![](https://docs.google.com/drawings/u/0/d/sLHPJgxqCymGiYcdIVrW8dQ/image?w=461&h=382&rev=15&ac=1&parent=1RpODTs_ukJqa39zscydEmW6fmhVRyLtL4GC0di6UGzM)

And you successfully compiled for C. The compiled file is ai.dll.

## Using C++

However, there are many stuff (like data structures, Object Oriented Programming) that you can get with only C++. Hence, most of the national players use C++.

To compile for C++, you have to install Cygwin and the C++ compiler on your computer, which you can find here [https://cygwin.com/setup-x86_64.exe](https://cygwin.com/setup-x86_64.exe). During the Cygwin install, take note to install the mingw-g++ C++ compiler. Also take note to add to Windows’ PATH Variable, like [here](https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/).

![](https://lh3.googleusercontent.com/W1KnbfB9wkUHLn4VpWkLZ15SisN5p7xT70Y-5JBjEe1IO_Yznh2gcB19vJMiDD5eBlZZY8HOCj0lITuhSEoHGNv5iZEvWSWF93yiPVfPXe8PNtxdIw2MBZXIV9RdQmcge4jbaHsl)![](https://lh6.googleusercontent.com/WzEfL3qyH22n1tteIlCExtvF-DrnHc3YBZFCHJr9ZLktDE9pMYVAAkQxcg60wWLkjiQ3uTl80gflzyCTpNFQnYLVW5unds22C_CQ2vHL6mTU16QxSvscL-j_O9P-oVGu8r6672rr)

Once you have installed the programs, you can just copy the code into a new file, ai.cpp.

However, you have to make some modifications to the code first in ai.cpp. You have to put extern “C”{...} over the DLL_EXPORT Functions, so that they will compile as C code, to be used in CoSpace Simulator

![](https://lh5.googleusercontent.com/9XfGaR3yA46ozEx5XoPcExjekBhC-n-h10L442K09QZtlLJlWvLT6acdXU2d8XR5IP4RSYLWNAlgFCYGho8k7YILUaq72V65x739C1dKtJ0BuqZAjHxdWF0JZTYvR_D0DHP4FvyL)

![](https://lh4.googleusercontent.com/7ZaPFQ8jH6SdJANMt4A-5DVoJeYZrYhFyqDeHeSCCRTS4FTuNrkGXaj5dQYygg5_drFufkcdyk51FnEkuMUDCVpsbF5KPy05gi2OMRe8cPV9MH5SR8OiCn9gOnuWaQYvOJny54IL)

The main commands to compile the code in the directory are
```
i686-w64-mingw32-g++ -O3 -shared -static -std=c++17 -Wall -Wextra ai.cpp -o ai.dll & REM 2> errors.txt
strip --strip-unneeded ai.dll
pause
```
You can change the ai.cpp and ai.dll files to the appropriate filenames if you want. You can put this command into a .bat file and run it.

![](https://lh6.googleusercontent.com/9UsT_Wb0zObI5pUBffX2f37FecbuKMJd9UgYpTf3vjhYOpzHTTDok58CZjUldJcISUcLbe_W5Z9y4kXdjOE8eo38NtwOrR12n-L44ecOc3AzarhpbCwYFjczqikDpXa_0L2mD679)

Nice it works! You can actually move most of the above code into a seperate header file (as you would not need them anymore), leaving only the main Game0() and Game1() functions in ai.cpp, like this.

![](https://lh6.googleusercontent.com/JfBctbZPajYCVzpi4ugAVnCTjT7YfNL37DnchyfUPJ1GzUv8HWrPgUMA0Jz347Oymz9ZOTPObJBkt71ZiKq0t5O_SJcYUCweZ7hZdR3uqkRKE5NV8Kcs4Ta_4hXqEdbFIBWgHoYX)

So much easier to read now! We will be using this code as a template for the next tutorials.

## Running some code!

Let’s start with a simple hello world program.

Firstly, we need to make some tweaks to the ai.c for it to run our code.

  

Right now we should change the bottom of the code like so. This is so that your code will run in the functions Game0() and Game1().

![](https://lh4.googleusercontent.com/2VtBQvdgav0gFGlszL4aawrXnRI6tHZC5ZTU6YxOJIehoPdyvEL8LQNEZ_9WgSbHPFfTTsC-W79XKTRNfd7wih3WgvB2ckqQcGbkaDP5mVaXXC38CIWqqktDDktMXofz1d3xXuYF)![](https://lh4.googleusercontent.com/KGzpNx38-Yy0EH09fXIqWs5kLsQl7c4213FfyuDbaqoA61vDW2ThxKdNBuFmfXfP7sQVNRAiHm4jA9vwcnBOuWRRXuZ7_C1B2v1Tl2NpW0UIS3vSkZHtdFWNA1tG5I4ZAolMXE2h)

This also means that you have to add this code before the DLL_EXPORT.

![](https://lh4.googleusercontent.com/8hIuJKgCDQyRUt_qE5VaRlxTNz1mJWp4m4F0i63PvpVLoni9ZEOtDiKeb-b_3cmh3kyM6TEVooidH917ka2mV1iKajDXKJWySofxq0D2PVpClKBglowkJc1Y_5Q1hFKJtF8JS6ES)

You can insert your team name into this function in the code

![](https://lh6.googleusercontent.com/dtHX2kp6ghxlXPGnXHNMCIze_ewBia9xXP2ZsaHYTPa-AwD9YZrFO5a-nie-fCEpuhs7Ma_aTqQa_obj2h1kZ49plL_IMOHvdW3MbDKyG_4_cEaB-0XwcqxD0BPVTtitWPy6GYWS)

Run your code. Click Load (Blue for blue robot, red for red robot), select your file, and then play.

![](https://lh3.googleusercontent.com/BtkuWQ5HANqLE5oqbNTeLdnvIFGxSdvdOIemjW5mtWbTUx7zYZ2U-GfCTtMf1hLjEgGHvstFB88LI2k18CILzWlmroZDVJCit3_XB0uNgD6ut_tJmxJEHCBPmYM71a6FK8x4aA--)

![](https://lh3.googleusercontent.com/oACHRiq8sjA4_jdAW70uqSIDYF6NyNCG8FYjMNeRiHBwl9UMhSBqefa7NINsfpyb6N7kw7deJmdLguSTYb_n4LNJswsgC_ppI3EdczztErWehxI11WLK5LtniOmQzBoX29_kxYmz)![](https://lh3.googleusercontent.com/BtkuWQ5HANqLE5oqbNTeLdnvIFGxSdvdOIemjW5mtWbTUx7zYZ2U-GfCTtMf1hLjEgGHvstFB88LI2k18CILzWlmroZDVJCit3_XB0uNgD6ut_tJmxJEHCBPmYM71a6FK8x4aA--)

When you click play your code in Game0() should run like above. However, to run your code in Game1(), click world2, load ai.dll again and then click play.

![](https://docs.google.com/drawings/u/0/d/sU7ZqK-Tmdo8Qp2Y8zYXFgA/image?w=267&h=208&rev=7&ac=1&parent=1RpODTs_ukJqa39zscydEmW6fmhVRyLtL4GC0di6UGzM)

![](https://lh5.googleusercontent.com/QmVECXJ9IuPk_lqJ5r-Jb3q91v6B_3hhSt7A8fV4x5oozRJcfrD_TdCPDkpyUeEBtWeLsHQ7159hYIXhdnZDVLG3MPOGDEy4OwwuEYCxaFYerstxWQ6hcqL3Wu8BzqLraYWRruY_)

Yay, the code works! So this is how to use Cospace Rescue Simulator in a nutshell. In the next tutorial, we would learn how to control the robot itself.
