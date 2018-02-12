# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\loone\Documents\GitHub\Zumo_Bot\Zumo.release\Zumo01\ZumoBot.cydsn\ZumoBot.cyprj
# Date: Mon, 12 Feb 2018 13:32:18 GMT
#set_units -time ns
create_clock -name {ADC_Battery_theACLK(routed)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/dclk_0}]]
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_clock -name {CyBUS_CLK(fixed-function)} -period 41.666666666666664 -waveform {0 20.8333333333333} [get_pins {ClockBlock/clk_bus_glb_ff}]
create_generated_clock -name {ADC_Battery_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 5} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {UART_1_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 27 53} -nominal_period 1083.3333333333333 [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {timer_clock_4} -source [get_pins {ClockBlock/clk_sync}] -edges {1 31 61} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/clk_sync}] -edges {1 121 241} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 241 481} [list [get_pins {ClockBlock/dclk_glb_4}]]
create_generated_clock -name {timer_clock_5} -source [get_pins {ClockBlock/clk_sync}] -edges {1 1201 2401} [list [get_pins {ClockBlock/dclk_glb_5}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\loone\Documents\GitHub\Zumo_Bot\Zumo.release\Zumo01\ZumoBot.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\loone\Documents\GitHub\Zumo_Bot\Zumo.release\Zumo01\ZumoBot.cydsn\ZumoBot.cyprj
# Date: Mon, 12 Feb 2018 13:32:09 GMT
