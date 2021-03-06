Configuring
===========

Each segment is made up of 6 parts. **Output handler**, **output generator**, **generator arguments**, **color**, **conditions**, **condition arguments**.

**Output handlers**
-------------------

| Name      | Effect                                                        |
| --------- | ------------------------------------------------------------- |
| string    | Displays what the function outputs, or otherwise the value    |
| percent   | Displays value/max with a %-sign                              |
| bar       | same as percent, but rendered with a nice bar                 |
| timeconv  | Convert value to time                                         |
| sizeconv  | Convert value to bytes. Precision of 2 decimals and KB, MB... |
| sizeconvi | Same as sizeconv but with KiB, MiB... instead                 |

**Output generators**
---------------------

| Name              | Arguments | Effect                                                    | Requires | Working |
| ----------------- | --------- | --------------------------------------------------------- | -------- | ------- |
| proc_load         | 0-3       | Returns average cpu load. 0: 1min 1: 5min 2: 15min 3: all |          | Yes     |
| proc_memory       |           | Returns memory usage                                      |          | Yes     |
| proc_cpu          |           | Returns cpu usage                                         |          | Yes     |
| proc_cpu_mhz      |           | Returns cpu MHz                                           |          | Yes     |
| proc_uptime       |           | Returns uptime as seconds                                 |          | Yes     |
| time_date         | strftime  | Returns date time formatted with                          |          | Yes     |
| battery_status    | battery   | Returns the status for the battery                        |          | Yes     |
| battery_capacity  | battery   | Returns the current capacity for the battery              |          | Yes     |
| battery_time      | battery   | Returns the time until discharged or charged              |          | Yes     |
| cpu_temp          |           | Returns the temperature of the first cpu                  |          | Yes     |
| network_ip        | interface | Returns the IP for the interface                          |          | Yes     |
| exec              | command   | Executes the command and returns the output               |          | Yes     |
| get_uname         | a,s,n,r,v | Returns information, like the uname program does          |          | Yes     |
| fs_total          | path      | Returns total available space in (mounted) path           |          | Yes     |
| fs_free           | path      | Returns total free space in (mounted) path                |          | Yes     |
| fs_used           | path      | Returns total used space in (mounted) path                |          | Yes     |
| downspeed         | interface | Returns current download speed for the interface          |          | Yes     |
| upspeed           | interface | Returns current upload speed for the interface            |          | Yes     |
| wireless_essid    | interface | Returns the network's ESSID for the interface             | iwlib    | Yes     |
| wireless_ap_addr  | interface | Returns the access point's hardware address               | iwlib    | No      |
| wireless_freq     | interface | Returns the network's frequency for the interface         | iwlib    | Partial |
| wireless_chan     | interface | Returns the network's channel for the interface           | iwlib    | No      |
| wireless_bitrate  | interface | Returns the network's bitrate for the interface           | iwlib    | No      |
| wireless_quality  | interface | Returns the network's  signal strength  for the interface | iwlib    | Yes     |
| alsa_volume       | channel   | Returns the volume of the channel                         | alsa     | Yes     |
| mpd_vera          |           | Returns MPD's major version number                        | mpd      | Yes     |
| mpd_verb          |           | Returns MPD's middle version number                       | mpd      | Yes     |
| mpd_verc          |           | Returns MPD's minor version number                        | mpd      | Yes     |
| mpd_qv            |           | Returns MPD's queue version                               | mpd      | Yes     |
| mpd_ql            |           | Returns MPD's queue (playlist) length                     | mpd      | Yes     |
| mpd_spos          |           | Returns MPD's currently playing song's position in queue  | mpd      | Yes     |
| mpd_sels          |           | Returns MPD's currently playing song's elapsed seconds    | mpd      | Yes     |
| mpd_selms         |           | Returns MPD's currently playing song's elased milliseconds| mpd      | Yes     |
| mpd_sbrat         |           | Returns MPD's currently playing song's bit rate           | mpd      | Yes     |
| mpd_afsr          |           | Returns MPD's currently playing song's sample rate        | mpd      | Yes     |
| mpd_afbits        |           | Returns MPD's currently playing song's bit amount         | mpd      | Yes     |
| mpd_afchan        |           | Returns MPD's currently playing song's channel amount     | mpd      | Yes     |
| mpd_ur            |           | Returns MPD's currently playing song's uri (file name)    | mpd      | Yes     |
| mpd_artist        |           | Returns MPD's currently playing song's artist             | mpd      | Yes     |
| mpd_album         |           | Returns MPD's currently playing song's album              | mpd      | Yes     |
| mpd_title         |           | Returns MPD's currently playing song's title              | mpd      | Yes     |
| mpd_track         |           | Returns MPD's currently playing song's track number       | mpd      | Yes     |
| mpd_name          |           | Returns MPD's currently playing song's name               | mpd      | Yes     |
| mpd_date          |           | Returns MPD's currently playing song's name               | mpd      | Yes     |
| mpd_smart         | separator | MPD's current song as artist - name if possible, else uri | mpd      | Yes     |

**Conditions**
--------------

| Name              | Arguments | Effect                                                    | Requires | Working |
| ----------------- | --------- | --------------------------------------------------------- | -------- | ------- |
| net_ifup          | interface | Returns 1 if interface is up                              |          | Yes     |
| net_ifdown        | interface | Returns 1 if interface is down                            |          | Yes     |
| bat_exists        | battery   | Returns 1 if battery exists                               |          | Yes     |
| bat_islow         | battery   | Returns 1 if battery capacity is under 20%                |          | Yes     |
| if_cpu_temp       |           | Returns 1 if haapa can get the cpu temperature            |          | Yes     |
| alsa_muted        | channel   | Returns 1 if channel is muted                             | alsa     | Yes     |
| mpd_playing       |           | Returns 1 if mpd is playing                               | mpd      | Yes     |

**Color**
---------

Color is given in a hex form, for example "#F0A090" would be a valid color. You can specify two colors to be flashed each other update like this: "#FFFFFF,#FF0000". This would be white for the first tick, then red, then white again, and so on.

**Global options**
------------------

| Name               | Arguments | Effect                                                    | Requires | Working |
| ------------------ | --------- | --------------------------------------------------------- | -------- | ------- |
| formatter          | format_*  | See [this table](#formats)                                |          | Yes     |
| outputter          | output_*  | Possible values: plain, ontop, x                          | x: Xlib  | Yes     |
| interval           | integer   | How often should haapa update, in seconds                 |          | Yes     |
| batpath            | path      | Path to where the systems batteries reside                |          | Yes     |
| segment_seperator  | string    | What string will seperate each segment in FORMAT_PLAIN    |          | Yes     |
| bar_format_unicode | integer   | How is the bar drawn. 0: no unicode, 1: vert 2: hori      |          | Yes     |
| bar_format         | string    | Whats aside the bar                                       |          | Yes     |
| bar_format_length  | integer   | How long are bars                                         |          | Yes     |

**Formats**
-----------

| Name             | Description                                                                 |
| ---------------- | --------------------------------------------------------------------------- |
| format_plain     | Very plain formatting. No colors are included. Suistable for terminals.     |
| format_i3        | Format made for use with i3bar.                                             |
| format_i3_manual | Format made for use with i3bar. Segments are defined manually in this one.  |
| format_dzen      | Format made for use with dzen.                                              |
| format_xmobar    | Format made for use with xmobar.                                            |
| format_x256      | Colored format for 256 color terminals. Useful for use with DWM.            |
| format_html      | HTML format with colors. Useful for generating HTML status pages.           |

**Notes**
---------

*   When using **format_i3_manual**, you control how segments (full_text) are created. You can start a new one using the macro "i3_manual_start()" and end your segments using "i3_manual_end(color)".

