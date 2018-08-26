# Remote command examples

```
begin
create s1 as steppermotor 1
create s2 as steppermotor 2
create pb1 as pushbutton 20
create dp2 as pin digital input 2
create dp13 as pin digital output 13
create ap1 as pin analog a1
do s1.begin
do s2.begin
do pb1.begin
do s1.rpm 200
do s2.rpm 60
wait pb1.pressed
do s1.step 20
do s2.rotate -3600
do s1.disable
wait not s1.running
get pb1.clicks
get dp2.value
get ap1.value
do s2.disable
do dp13.state high
end
```
