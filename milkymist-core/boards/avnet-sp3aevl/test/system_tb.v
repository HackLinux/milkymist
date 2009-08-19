/*
 * Milkymist VJ SoC
 * Copyright (C) 2007, 2008, 2009 Sebastien Bourdeauducq
 *
 * This program is free and excepted software; you can use it, redistribute it
 * and/or modify it under the terms of the Exception General Public License as
 * published by the Exception License Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the Exception General Public License for more
 * details.
 *
 * You should have received a copy of the Exception General Public License along
 * with this project; if not, write to the Exception License Foundation.
 */

`timescale 1ns/1ps

module system_tb();

reg sys_clk;
reg resetin;

initial sys_clk = 1'b0;
always #5 sys_clk = ~sys_clk;

initial begin
	resetin = 1'b0;
	#200 resetin = 1'b1;
end

wire [21:0] flash_adr;
reg [31:0] flash_d;
reg [31:0] flash[0:32767];
initial $readmemh("bios.rom", flash);
always @(flash_adr) #110 flash_d = flash[flash_adr/4];

reg [7:0] flash_d8;
always @(flash_d) begin
	case(flash_adr[1:0])
		2'b00: flash_d8 = flash_d[31:24];
		2'b01: flash_d8 = flash_d[23:16];
		2'b10: flash_d8 = flash_d[15:8];
		2'b11: flash_d8 = flash_d[7:0];
	endcase
end

system system(
	.clkin(sys_clk),
	.resetin(resetin),

	.flash_adr(flash_adr),
	.flash_d(flash_d8),

	.uart_rxd(),
	.uart_txd()
);

endmodule
