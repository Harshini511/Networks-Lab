set ns [new Simulator]

$ns color 0 blue
$ns color 1 red
$ns color 2 green
$ns color 3 yellow

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]

set f [open out1.tr w]
$ns trace-all $f
set nf [open out1.nam w]
$ns namtrace-all $nf

$ns duplex-link $n0 $n1 5Mb 2ms DropTail
$ns duplex-link $n1 $n2 1.5Mb 10ms DropTail
$ns duplex-link $n2 $n3 5Mb 2ms DropTail
$ns duplex-link $n1 $n4 5Mb 2ms DropTail
$ns duplex-link $n2 $n5 5Mb 2ms DropTail
$ns duplex-link $n1 $n6 5Mb 2ms DropTail
$ns duplex-link $n2 $n7 5Mb 2ms DropTail

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n6 $n1 orient right-up
$ns duplex-link-op $n4 $n1 orient right-down
$ns duplex-link-op $n1 $n2 orient right
$ns duplex-link-op $n2 $n3 orient right-up
$ns duplex-link-op $n2 $n5 orient right
$ns duplex-link-op $n2 $n7 orient right-down

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
$udp0 set class_ 0
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0

set udp1 [new Agent/UDP]
$ns attach-agent $n6 $udp1
$udp1 set class_ 1
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1

set null0 [new Agent/Null]
$ns attach-agent $n3 $null0

set null1 [new Agent/Null]
$ns attach-agent $n3 $null1

$ns connect $udp0 $null0
$ns connect $udp1 $null0

$ns at 1.0 "$cbr0 start"
$ns at 1.1 "$cbr1 start"

set tcp0 [new Agent/TCP]
$ns attach-agent $n4 $tcp0
$tcp0 set class_ 2
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set tcp1 [new Agent/TCP]
$ns attach-agent $n5 $tcp1
$tcp1 set class_ 3
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1

set sink0 [new Agent/TCPSink]
$ns attach-agent $n7 $sink0
set sink1 [new Agent/TCPSink]
$ns attach-agent $n6 $sink1

$ns connect $tcp0 $sink0
$ns connect $tcp1 $sink1

$ns at 1.2 "$ftp0 start"
$ns at 1.3 "$ftp1 start"

puts [$cbr0 set packetSize_]
puts [$cbr0 set interval_]

$ns at 3.0 "finish"

proc finish {} {
global ns f nf
$ns flush-trace
close $f
close $nf

puts "running nam..."
exec nam out1.nam &
exit 0
}

$ns run