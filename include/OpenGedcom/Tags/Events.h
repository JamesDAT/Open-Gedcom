// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class BirthTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BIRT";

        explicit BirthTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class DeathTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "DEAT";

        explicit DeathTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class MarriageTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "MARR";

        explicit MarriageTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class BurriedTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BURI";

        explicit BurriedTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class EventTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EVEN";

        explicit EventTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class OrdinationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ORDN";

        explicit OrdinationTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class ImmigrationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "IMMI";

        explicit ImmigrationTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class EmigrationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EMIG";

        explicit EmigrationTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class WillTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "WILL";

        explicit WillTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class AdoptionTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ADOP";

        explicit AdoptionTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class BaptismTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BAPM";

        explicit BaptismTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class BarMitzvahTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BARM";

        explicit BarMitzvahTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class BasMitzvahTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BASM";

        explicit BasMitzvahTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class BlessingTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BLES";

        explicit BlessingTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class AdultChristeningTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHRA";

        explicit AdultChristeningTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class ChristeningTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHR";

        explicit ChristeningTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class ConfirmationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CONF";

        explicit ConfirmationTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class ConfirmationLdsTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CONL";

        explicit ConfirmationLdsTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class CremationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CREM";

        explicit CremationTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class EngagementTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ENGA";

        explicit EngagementTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class NaturalizationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NATU";

        explicit NaturalizationTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class ProbateTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PROB";

        explicit ProbateTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class RetirementTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "RETI";

        explicit RetirementTag(std::string_view value)
            : GedcomTag(value) {}
    };

}