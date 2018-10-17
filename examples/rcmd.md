# Remote command examples

```
ping

create s1 as stepper 1
set s1 rpm 200
do s1 step 20
get s1 stepsremaining
do s1 disable
do s1 reset


create s2 as stepper 2
set s2 rpm 60
set s2 microsteps 32
do s2 rotate -3600
get s2 stepsremaining
do s2 disable


create pb1 as pushbutton 20
get pb1 clicks
get pb1 state
get pb1 pin

create dp2 as pin digital input 2
get dp2 value

create dp13 as pin digital output 13
set dp13 value 1
get dp13 value
get dp13 pin

create ap1 as pin analog input a1
get ap1 value
get ap1 pin









```
