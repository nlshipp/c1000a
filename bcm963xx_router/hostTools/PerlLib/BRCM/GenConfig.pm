
use strict;
use warnings;

package BRCM::GenConfig;

sub new {
    my $class = shift;
    my $file  = shift;
    my $self  = {};
    my $mode  = '<';
    if ( -w $file ) {
        $mode = '+<';
    }
    open( my $fh, $mode, $file ) or die("couldnt open file '$file'");
    my $orig;
    {
        local $/;
        $orig = <$fh>;
    }
    my @lines = split( /\n/, $orig );
    seek( $fh, 0, 0 );
    $self->{file}  = $fh;
    $self->{lines} = \@lines;
    return bless( $self, $class );
}

sub set {
    my $self  = shift;
    my $var   = shift;
    my $val   = shift;
    my $lines = $self->{lines};
    my $i;
    for ( $i = 0 ; $i < @{$lines} ; $i++ ) {
        if ( $lines->[$i] =~ /(^$var=|^#\s*$var is)/ ) {
            last;
        }
    }
    if ( defined($val) ) {
        $lines->[$i] = "$var=$val";
    }
    else {
        $lines->[$i] = "# $var is not set";
    }
    return 1;
}

sub notset {
    my $self = shift;
    my $var  = shift;
    return $self->set($var);
}

sub write {
    my $self = shift;
    my $file = shift;
    my $fh;
    if ($file) {
        open( $fh, ">", $file ) or die("cant write $file");
    }
    else {
        $fh = $self->{file};
        seek( $fh, 0, 0 );
	truncate($fh, 0);
    }
    print $fh join( "\n", @{ $self->{lines} } ) ;
    print $fh "\n";
    if ($file) {
        close($fh);
    }

    return 1;
}

1;

__END__

=head1 NAME

BRCM::GenConfig -- In-place editing of kconfig-type files

=head1 SYNOPSIS

    use strict;
    use warnings;
    use BRCM::GenConfig;

    my $g = new BRCM::GenConfig('.config'); # open the file
    $g->set( "CONFIG_PREFIX", "string" ); # set/create a value

    $g->set( "CONFIG_FEATURE_WGET_HTTPS", "y" ); # set/create
    $g->set( "CONFIG_FEATURE_WGET_AUTHENTICATION" ); # is not set
    }

    $g->write();
    or
    $g->write("newfile");

=cut

