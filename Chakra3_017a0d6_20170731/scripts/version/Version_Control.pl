#!/usr/bin/perl

#####
## SYNTAX:
## perl Version_Control.pl file_list.txt source_path
#####

use warnings;
use strict;

use Cwd;

my $fileList = shift;
my $srcPath = shift || "";

my $getVersionVersion = '$Revision: #13 $';
my $getChangeList     = '$Change: 1148623 $';
my $pwd = cwd();
my %hash_result;
my $count = 0;
my $versionResult = "version_result.txt";
my $parse_format = "";

sub parseKernal
{
	my $file_name = shift;
	my $module = shift;
	
	my $ver_command = "";
	my @ver_result = ();
	my $kernel_ver = "";
	my $driver_ver = "";
	
	if(! -e "$file_name")
	{
    	chomp($file_name);
    	$hash_result{"$file_name\(Kernel\)"} = "[No such file]";
        $hash_result{"$file_name\(Kernel\)"} = sprintf "%-20s %s",$module, $hash_result{"$file_name\(Kernel\)"};	    
        return;
	}
	
	$ver_command = 'strings '.$file_name.' | grep "KERN-"';
	#print "cmd:$ver_command\n";
    # new format
    $kernel_ver = `$ver_command`;
    $kernel_ver =~ s/\n$//;
    $kernel_ver =~ s/\s+$//;    
	chomp($file_name);
	$hash_result{"$file_name\(Kernel\)"} = ($kernel_ver eq "")?"[NO_KERVER]":$kernel_ver;
    $hash_result{"$file_name\(Kernel\)"} = sprintf "%-20s %s",$module, $hash_result{"$file_name\(Kernel\)"};
}

sub parseMboot
{
	my $file_name = shift;
	my $module = shift;
	
	my $ver_command = "";
	my @ver_result = ();
	my $kernel_ver = "";
	my $driver_ver = "";
	
	if(! -e "$file_name")
	{
    	chomp($file_name);
    	$hash_result{"$file_name\(MBoot\)"} = "[No such file]";
        $hash_result{"$file_name\(MBoot\)"} = sprintf "%-20s %s",$module, $hash_result{"$file_name\(MBoot\)"};	    
        return;
	}
	
	$ver_command = 'strings '.$file_name.' | grep "MBOT-"';
	#print "cmd:$ver_command\n";
    # new format
    $kernel_ver = `$ver_command`;
    $kernel_ver =~ s/\n$//;
    $kernel_ver =~ s/\s+$//;    
	chomp($file_name);
	$hash_result{"$file_name\(MBoot\)"} = ($kernel_ver eq "")?"[NO_KERVER]":$kernel_ver;
    $hash_result{"$file_name\(MBoot\)"} = sprintf "%-20s %s",$module, $hash_result{"$file_name\(MBoot\)"};
}

sub parseTxt
{
    my $path = shift;
	my $module = shift;
	
    my $ver = "[NO_KERVER]";
	
	if(! -e "$path")
	{
    	chomp($path);
    	$ver = sprintf "%-20s [No such file]",$module;
    	$hash_result{"$path\(Txt\)"} = "$ver";	
        return;
	}	
	open(SNCL_FILE, "<$path") or die "Could not open $path";

	while ($ver = <SNCL_FILE>)
	{
	    last;
	}
    close(SNCL_FILE);
	$ver =~ s/\n//;
	$ver = sprintf "%-20s %s",$module,$ver;
	print "$module => $ver\n";

    $hash_result{"$path\(Txt\)"} = "$ver";
}

sub parseMSIF
{
	my $file_name = shift;
	my $module = shift;
	my $gzFile = shift;
	
	my $msif = "";
	
	if($gzFile ne "")
	{
	    $gzFile = " @".$gzFile;
	}
	if(! -e "$file_name")
	{
        chomp($file_name);
        $hash_result{"$file_name\(MSIF\)$gzFile"} = "[No such file]";
        $hash_result{"$file_name\(MSIF\)$gzFile"} = sprintf "%-20s %s",$module, $hash_result{"$file_name\(MSIF\)$gzFile"};
        return;
	}	
	open(MSIF_FILE, "$file_name") or die("Could not open $file_name.\n");
	my @msifContant = <MSIF_FILE>;
	close(MSIF_FILE);
	for my $msifline (@msifContant)
	{
		if ($msifline !~ /MSIF_Version/)
		{
			if ($msifline =~ /MSIF/)
			{
				$msif = substr($', 9, 16); #'
				# conver "MM300106004288820" to "MM30-01.06.00428882"
				
				my $f03;
				my $f45;
				my $f67;
				my $f815;
				$f03 = substr($msif, 0, 4);
				$f45 = substr($msif, 4, 2);
				$f67 = substr($msif, 6, 2);
				$f815 = substr($msif, 8, 8);
				$msif = "$f03-$f45".".".$f67.".".$f815;
				print "$msif\n";
				last;
			}
		}
	}
	chomp($file_name);
	$hash_result{"$file_name\(MSIF\)$gzFile"} = (($msif eq "")?"[NO_MSIF]":$msif);
	$hash_result{"$file_name\(MSIF\)$gzFile"} = sprintf "%-20s %s",$module, $hash_result{"$file_name\(MSIF\)$gzFile"};
}

sub parseElf
{
	my $file_name = shift;
	my $module = shift;
	my $gzFile = shift;
	
	my $ver_command = "";
	my @ver_result = ();
	my $libcode = "";
	my $libver = "";
	my $buildnum = "";
	my $change = "";

	if($gzFile ne "")
	{
	    $gzFile = " @".$gzFile;
	}
	if(! -e "$file_name")
	{
    	chomp($file_name);
    	$hash_result{"$file_name\(Elf\)$gzFile"} = "[No such file]";
        $hash_result{"$file_name\(Elf\)$gzFile"} = sprintf "%-20s %s",$module, $hash_result{"$file_name\(Elf\)$gzFile"};        
        return;
	}
	
	$ver_command = 'readelf --string-dump=.mmodule_version '.$file_name;
	@ver_result = `$ver_command`;
	
	for(my $i=0; $i<=$#ver_result; $i++)
	{
		if($ver_result[$i] ne "\n")
		{
			$ver_result[$i] =~ s/\n//;
			
			if( $ver_result[$i] =~ /LIBCODE/ )
			{
				$ver_result[$i] =~ s/\s+//g; 	#replace the spaces
				print "$ver_result[$i] => ";
				if($ver_result[$i] =~ /:(\w+)/)
				{
					$libcode = $1;
					print "$libcode\n";
					next;
				}
			}
			
			if( $ver_result[$i] =~ /LIBVER/ )
			{
				$ver_result[$i] =~ s/\s+//g; 	#replace the spaces
				print "$ver_result[$i] => ";
				if($ver_result[$i] =~ /:([A-Za-z0-9-.]+)/)
				{
					$libver = $1;
					print "$libver\n";
					next;
				}
			}
			
			if( $ver_result[$i] =~ /BUILDNUM/ )
			{
				$ver_result[$i] =~ s/\s+//g; 	#replace the spaces
				print "$ver_result[$i] => ";
				if($ver_result[$i] =~ /:(\w+)/)
				{
					$buildnum = $1;
					print "$buildnum\n";
					next;
				}
			}
			
			if( $ver_result[$i] =~ /Change/ )
			{
				$ver_result[$i] =~ s/\s+//g; 	#replace the spaces
				print "$ver_result[$i] => ";
				if($ver_result[$i] =~ /:(\w+)/)
				{
					$change = $1;
					print "$change\n";
					next;
				}
			}
		}
	}
	
	chomp($file_name);
	$hash_result{"$file_name\(Elf\)$gzFile"} = (($libcode eq "")?"[NO_LIBCODE]":$libcode)."-".
		(($libver eq "")?"[NO_LIBVER]":$libver).
		".".(($buildnum eq "")?"[NO_BUILDNUM]":$buildnum).
		".".(($change eq "")?"[NO_CHANGE]":$change);
    $hash_result{"$file_name\(Elf\)$gzFile"} = sprintf "%-20s %s",$module, $hash_result{"$file_name\(Elf\)$gzFile"};
}

sub parseFile()
{
    my $parsedFile = $_[0];
    my $module = $_[1];
    #if ($parsedFile =~ /\.tar\.gz\//)
    if ($parsedFile =~ /\.tgz\// || $parsedFile =~ /\.tar\.gz\//)
	{
		my $tarFile = $parsedFile;
		my $tarFname = $'; #'
		$tarFile =~ s/\/$tarFname//;
		
		if (-e "$pwd/tmp")
        {
        	system "rm -rf $pwd/tmp";
        }
		mkdir "$pwd/tmp";
		
		my @fname = split(/\//, $tarFile);
		my $path = $tarFile;
		$path =~ s/$fname[$#fname]//;
		chdir $path;
		system "tar -zx -f $fname[$#fname] -C $pwd/tmp";
		chdir $pwd;
		
		my $displayTarFile = $tarFile;
		$displayTarFile =~ s/^\.//;
		$displayTarFile =~ s/^\///;
		if ($parse_format eq "MSIF")
		{
			parseMSIF("$pwd/tmp/$tarFname", $module, $displayTarFile);
		}
		elsif ($parse_format eq "Elf")
		{
			parseElf("$pwd/tmp/$tarFname", $module, $displayTarFile);
		}
	}
	elsif ($parsedFile =~ /MBoot/)
	{
		parseMboot($parsedFile, $module);
	}
	elsif ($parsedFile =~ /uImage$/)
	{
		parseKernal($parsedFile, $module);
	}
	elsif ($parse_format eq "MSIF")
	{
		parseMSIF($parsedFile, $module, "");
	}
	elsif ($parse_format eq "Elf")
	{
		parseElf($parsedFile, $module, "");
	}
	elsif ($parse_format eq "Txt")
	{
	    parseTxt($parsedFile, $module);
	}	
}

#main code
open(FILE_LIST, "$fileList") or die("Could not open $fileList.\n");
print "Open the file \"$fileList\"\n";

my $module = "";

foreach my $line (<FILE_LIST>)
{
	$line =~ s/\n//;
	
    $line =~ s/^\s+//; # remove whitespace from the begin of the string

	if($line =~ /^\/\//)
	{
	    print "Comment: $line \n";
	    next
	}
	elsif ($line =~ /^#/)
	{
	    ##MSDK(Elf)
		if ($line =~/^#(.*)\(Elf\)$/)
		{
		    $module = $1;
			$parse_format = "Elf";
		}
		##Vdplayer(MSIF)
		elsif ($line =~/^#(.*)\(MSIF\)$/)
		{
		    $module = $1;
			$parse_format = "MSIF";
		}
		elsif ($line =~/^#(.*)\(Txt\)$/)
		{
		    $module = $1;
			$parse_format = "Txt";
		}		
		elsif ($line =~/^#(.*)$/)
		{
		    $module = $1;
		}
		
		next;
	}
	elsif ($line eq "")
	{
        $module = "";
		next;
	}
	
	if ($srcPath ne "")
	{
		$srcPath =~ s/\\/\//g;
		if ($srcPath !~ /\/$/)
		{
			$srcPath = $srcPath."\/";
		}
		$line = $srcPath.$line;
	}
	
	print "\n========".$count."=======\n";
	$count++;
	if ($line =~ /\*/)
	{
		my @fname = split(/\//, $line);
		my $path = $line;
		$fname[$#fname] =~ s/\*/\\\*/g;
		$path =~ s/$fname[$#fname]//;
		$fname[$#fname] =~ s/\\\*/\*/g;
		chdir $path;
		my @fileName_s = <$fname[$#fname]>;
		chdir $pwd;
		for (0 ... $#fileName_s)
		{
			if ($parse_format eq "MSIF")
			{
				parseMSIF("$path/$fileName_s[$_]", $module, "");
			}
			elsif ($parse_format eq "Elf")
			{
				parseElf("$path/$fileName_s[$_]", $module, "");
			}
		}
	}
	else
	{   
	    my $cmpStr = $line;
	    if ($srcPath ne "")
	    {
	        $cmpStr =~ s/$srcPath//;
	    }
	    if ($cmpStr =~ /^find\:/)
	    {
	        my $flagTarGzFile = 0; # 1: tar.gz file, 0: not a tar.gz file
	        my $tarGzBinFindFile;
	        my ($stdout, $stderr, $ret);
	        my $cmd;
	        my $findPath = $srcPath;
	        my $findFile;
	        my $flagFound = 0;
	        
            if ($findPath eq "") 
            {
                $findPath = ".";
            }
            
            $findFile = $line;
            $findFile =~ s/^find\://;
            
            if ($findFile =~ /\.tar\.gz/)
            {
                $flagTarGzFile = 1;
                $tarGzBinFindFile = "$findFile";
                if ($tarGzBinFindFile =~ /'(.*)'(.*)/)
                {
                    $findFile = "'".$1."'";
                    $tarGzBinFindFile = $2;
                    #print "$tarGzBinFindFile\n";
                }
                else 
                {
                    # find:'mmsdk.tar.gz'/mmsdk/libmmsdk.so
                    die("[".__PACKAGE__."][".__LINE__."]Format incorrect!\n");
                }
            }
            
	        $cmd = "find $findPath -name $findFile";
            print "$cmd\n";
            $stdout = `$cmd`;            
            foreach(split('\n', $stdout))
            {
                my $findFile = $_;
                
                $findFile =~ s/^\s+//; # remove whitespace from the begin of the string
                $findFile =~ s/\s+$//; # remove whitespace from the end of the string
                
                if ($flagTarGzFile eq 1)
                {
                    $findFile = $findFile."$tarGzBinFindFile";
                }
                print "**************************************\n";
                print "$findFile \n";
                &parseFile($findFile, $module);
                $flagFound = 1;
            }
            if($flagFound eq 0)
            {
                 print "File not found!\n";
            }
	    }
		else
		{
		    &parseFile($line, $module);
		}	
	}
}

open FILE, "+>", $versionResult or die("Could not create version result txt.\n");

#print all versions
print "\n==================== All Version ======================================\n";

print FILE "//!========================================================\n";
print FILE "CI Version\n";
print FILE "//!========================================================\n";

my @result = keys %hash_result;
sub cmpFun()
{
    my @arrStrListA = split(" ", $hash_result{$a});
    my $moduleA = lc($arrStrListA[0]);
    my @arrStrListB = split(" ", $hash_result{$b});
    my $moduleB = lc($arrStrListB[0]);
    
    if ($moduleA eq $moduleB) 
    {
    	my $filepathA = $a;
    	$filepathA =~ s/^$pwd//;
    	$filepathA =~ s/^\.//;
    	$filepathA =~ s/^\/tmp\///;
    	$filepathA =~ s/^\///;
    	my $filepathB = $b;
    	$filepathB =~ s/^$pwd//;
    	$filepathB =~ s/^\.//;
    	$filepathB =~ s/^\/tmp\///;
    	$filepathB =~ s/^\///;

        return $filepathA cmp $filepathB;
    }
    
    return $moduleA cmp $moduleB;
}
@result = sort cmpFun @result;

my $lastModule = "";
my $counter = 0;
foreach my $key (@result) 
{
    my @arrStrList = split(" ", $hash_result{$key});
    my $currModule = $arrStrList[0];
    my $resultStr = $hash_result{$key};
	my $strLen = length($resultStr);
	if ($strLen < 58)
	{
	    my $i;
	    for ($i = $strLen; $i < 58; $i++)
	    {
	        $resultStr .= " ";
	    }
	}
	my $filepath = $key;
	$filepath =~ s/^$pwd//;
	$filepath =~ s/^\.//;
	$filepath =~ s/^\/tmp\///;
	$filepath =~ s/^\///;

	if (($counter ne 0) && ($lastModule ne $currModule))
	{
	    print "-----------------------------------------------------------------------\n";
	}
    
	print "File = $filepath\nVersion = $resultStr\n";
	$lastModule = $currModule;
	print FILE "$resultStr File:$filepath\n";
	$counter++;
}
print FILE "//@========================================================\n";
print "\nVersion tool: $getVersionVersion    $getChangeList\n";
print FILE "Version tool: $getVersionVersion    $getChangeList\n";

close(FILE);
close(FILE_LIST);

if (-e "$pwd/tmp")
{
	system "rm -rf $pwd/tmp";
}
