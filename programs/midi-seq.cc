#include <fmidi/fmidi.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <memory>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    fmidi_smf_u smf(fmidi_smf_file_read(argv[1]));
    if (!smf) {
        fmt::print(std::cerr, "%s\n", fmidi_strerror(fmidi_errno()));
        return 1;
    }

    fmidi_seq_u seq(fmidi_seq_new(smf.get()));
    if (!seq) {
        fmt::print(std::cerr, "%s\n", fmidi_strerror(fmidi_errno()));
        return 1;
    }

    fmt::print("(midi-sequence");
    fmidi_seq_event_t plevt;
    while (fmidi_seq_next_event(seq.get(), &plevt)) {
        const fmidi_event_t *evt = plevt.event;
        fmt::print(std::cout, "\n  ({:<3} {:<12.6f} {})",
                   plevt.track, plevt.time, *evt);
    }
    fmt::print(")\n");

    return 0;
}
