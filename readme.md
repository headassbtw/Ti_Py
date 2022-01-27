# TiPy

A simple (ish) C++ app that aims to be a drop-in replacement or emulator to a Ti-84 Plus CE Python edition's python interpreter

Mostly just an SDL wrapper for the `ti_plotlib` library



# Functions

## ti_plotlib
 - [x] cls()
 - [ ] grid(xscl,yscl,"style")
    - [x] xscl
    - [x] yscl
    - [ ] "style"
 - [x] window(xmin,xmax,ymin,ymax)
 - [ ] auto_window(xlist,ylist)
 - [ ] axes("mode")
 - [ ] labels("xlabel","ylabel",x,y)
 - [ ] title("title")
 - [ ] show_plot()
 - [x] color(r,g,b)
 - [ ] scatter(xlist,ylist,"mark")
 - [x] plot(xlist,ylist,"mark")
 - [x] plot(x,y,"mark")
    - [x] x
    - [x] y
    - [x] "mark"
 - [ ] line(x1,y1,x2,y2,"mode")
    - [x] x1
    - [x] y1
    - [x] x2
    - [x] y2
    - [ ] "mode"
 - [ ] lin_reg(xlist,ylist,"disp")
 - [ ] pen("size","style")
 - [x] text_at(row,"text","align")

## ti_system
 - [x] var=recall_list("name")
 - [x] store_list("name",var)
 - [ ] var=recall_RegEQ()
 - [ ] while not escape():
 - [ ] if escape():break
 - [x] disp_at(row,"text","align")
 - [ ] disp_clr()
 - [x] disp_wait()
 - [ ] disp_cursor()
