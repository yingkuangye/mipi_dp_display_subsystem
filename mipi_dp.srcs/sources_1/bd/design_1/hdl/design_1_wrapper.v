//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
//Date        : Sat Oct 19 16:50:09 2024
//Host        : isuc-fifty-five running 64-bit Debian GNU/Linux 12 (bookworm)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (cam_gpio_tri_io,
    cam_i2c_scl_io,
    cam_i2c_sda_io,
    ddr4_rtl_0_act_n,
    ddr4_rtl_0_adr,
    ddr4_rtl_0_ba,
    ddr4_rtl_0_bg,
    ddr4_rtl_0_ck_c,
    ddr4_rtl_0_ck_t,
    ddr4_rtl_0_cke,
    ddr4_rtl_0_cs_n,
    ddr4_rtl_0_dm_n,
    ddr4_rtl_0_dq,
    ddr4_rtl_0_dqs_c,
    ddr4_rtl_0_dqs_t,
    ddr4_rtl_0_odt,
    ddr4_rtl_0_reset_n,
    diff_clock_rtl_0_clk_n,
    diff_clock_rtl_0_clk_p,
    mipi_phy_if_clk_n,
    mipi_phy_if_clk_p,
    mipi_phy_if_data_n,
    mipi_phy_if_data_p);
  inout [0:0]cam_gpio_tri_io;
  inout cam_i2c_scl_io;
  inout cam_i2c_sda_io;
  output ddr4_rtl_0_act_n;
  output [16:0]ddr4_rtl_0_adr;
  output [1:0]ddr4_rtl_0_ba;
  output [0:0]ddr4_rtl_0_bg;
  output [0:0]ddr4_rtl_0_ck_c;
  output [0:0]ddr4_rtl_0_ck_t;
  output [0:0]ddr4_rtl_0_cke;
  output [0:0]ddr4_rtl_0_cs_n;
  inout [3:0]ddr4_rtl_0_dm_n;
  inout [31:0]ddr4_rtl_0_dq;
  inout [3:0]ddr4_rtl_0_dqs_c;
  inout [3:0]ddr4_rtl_0_dqs_t;
  output [0:0]ddr4_rtl_0_odt;
  output ddr4_rtl_0_reset_n;
  input diff_clock_rtl_0_clk_n;
  input diff_clock_rtl_0_clk_p;
  input mipi_phy_if_clk_n;
  input mipi_phy_if_clk_p;
  input [1:0]mipi_phy_if_data_n;
  input [1:0]mipi_phy_if_data_p;

  wire [0:0]cam_gpio_tri_i_0;
  wire [0:0]cam_gpio_tri_io_0;
  wire [0:0]cam_gpio_tri_o_0;
  wire [0:0]cam_gpio_tri_t_0;
  wire cam_i2c_scl_i;
  wire cam_i2c_scl_io;
  wire cam_i2c_scl_o;
  wire cam_i2c_scl_t;
  wire cam_i2c_sda_i;
  wire cam_i2c_sda_io;
  wire cam_i2c_sda_o;
  wire cam_i2c_sda_t;
  wire ddr4_rtl_0_act_n;
  wire [16:0]ddr4_rtl_0_adr;
  wire [1:0]ddr4_rtl_0_ba;
  wire [0:0]ddr4_rtl_0_bg;
  wire [0:0]ddr4_rtl_0_ck_c;
  wire [0:0]ddr4_rtl_0_ck_t;
  wire [0:0]ddr4_rtl_0_cke;
  wire [0:0]ddr4_rtl_0_cs_n;
  wire [3:0]ddr4_rtl_0_dm_n;
  wire [31:0]ddr4_rtl_0_dq;
  wire [3:0]ddr4_rtl_0_dqs_c;
  wire [3:0]ddr4_rtl_0_dqs_t;
  wire [0:0]ddr4_rtl_0_odt;
  wire ddr4_rtl_0_reset_n;
  wire diff_clock_rtl_0_clk_n;
  wire diff_clock_rtl_0_clk_p;
  wire mipi_phy_if_clk_n;
  wire mipi_phy_if_clk_p;
  wire [1:0]mipi_phy_if_data_n;
  wire [1:0]mipi_phy_if_data_p;

  IOBUF cam_gpio_tri_iobuf_0
       (.I(cam_gpio_tri_o_0),
        .IO(cam_gpio_tri_io[0]),
        .O(cam_gpio_tri_i_0),
        .T(cam_gpio_tri_t_0));
  IOBUF cam_i2c_scl_iobuf
       (.I(cam_i2c_scl_o),
        .IO(cam_i2c_scl_io),
        .O(cam_i2c_scl_i),
        .T(cam_i2c_scl_t));
  IOBUF cam_i2c_sda_iobuf
       (.I(cam_i2c_sda_o),
        .IO(cam_i2c_sda_io),
        .O(cam_i2c_sda_i),
        .T(cam_i2c_sda_t));
  design_1 design_1_i
       (.cam_gpio_tri_i(cam_gpio_tri_i_0),
        .cam_gpio_tri_o(cam_gpio_tri_o_0),
        .cam_gpio_tri_t(cam_gpio_tri_t_0),
        .cam_i2c_scl_i(cam_i2c_scl_i),
        .cam_i2c_scl_o(cam_i2c_scl_o),
        .cam_i2c_scl_t(cam_i2c_scl_t),
        .cam_i2c_sda_i(cam_i2c_sda_i),
        .cam_i2c_sda_o(cam_i2c_sda_o),
        .cam_i2c_sda_t(cam_i2c_sda_t),
        .ddr4_rtl_0_act_n(ddr4_rtl_0_act_n),
        .ddr4_rtl_0_adr(ddr4_rtl_0_adr),
        .ddr4_rtl_0_ba(ddr4_rtl_0_ba),
        .ddr4_rtl_0_bg(ddr4_rtl_0_bg),
        .ddr4_rtl_0_ck_c(ddr4_rtl_0_ck_c),
        .ddr4_rtl_0_ck_t(ddr4_rtl_0_ck_t),
        .ddr4_rtl_0_cke(ddr4_rtl_0_cke),
        .ddr4_rtl_0_cs_n(ddr4_rtl_0_cs_n),
        .ddr4_rtl_0_dm_n(ddr4_rtl_0_dm_n),
        .ddr4_rtl_0_dq(ddr4_rtl_0_dq),
        .ddr4_rtl_0_dqs_c(ddr4_rtl_0_dqs_c),
        .ddr4_rtl_0_dqs_t(ddr4_rtl_0_dqs_t),
        .ddr4_rtl_0_odt(ddr4_rtl_0_odt),
        .ddr4_rtl_0_reset_n(ddr4_rtl_0_reset_n),
        .diff_clock_rtl_0_clk_n(diff_clock_rtl_0_clk_n),
        .diff_clock_rtl_0_clk_p(diff_clock_rtl_0_clk_p),
        .mipi_phy_if_clk_n(mipi_phy_if_clk_n),
        .mipi_phy_if_clk_p(mipi_phy_if_clk_p),
        .mipi_phy_if_data_n(mipi_phy_if_data_n),
        .mipi_phy_if_data_p(mipi_phy_if_data_p));
endmodule
