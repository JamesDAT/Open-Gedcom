// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class BirthTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BIRT";

        using GedcomTag::GedcomTag;
    };



    class DeathTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "DEAT";

        using GedcomTag::GedcomTag;
    };



    class MarriageTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "MARR";

        using GedcomTag::GedcomTag;
    };



    class BurriedTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BURI";

        using GedcomTag::GedcomTag;
    };



    class EventTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EVEN";

        using GedcomTag::GedcomTag;
    };



    class OrdinationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ORDN";

        using GedcomTag::GedcomTag;
    };



    class ImmigrationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "IMMI";

        using GedcomTag::GedcomTag;
    };



    class EmigrationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EMIG";

        using GedcomTag::GedcomTag;
    };



    class WillTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "WILL";

        using GedcomTag::GedcomTag;
    };



    class AdoptionTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ADOP";

        using GedcomTag::GedcomTag;
    };



    class BaptismTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BAPM";

        using GedcomTag::GedcomTag;
    };



    class BarMitzvahTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BARM";

        using GedcomTag::GedcomTag;
    };



    class BasMitzvahTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BASM";

        using GedcomTag::GedcomTag;
    };



    class BlessingTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BLES";

        using GedcomTag::GedcomTag;
    };



    class AdultChristeningTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHRA";

        using GedcomTag::GedcomTag;
    };



    class ChristeningTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHR";

        using GedcomTag::GedcomTag;
    };



    class ConfirmationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CONF";

        using GedcomTag::GedcomTag;
    };



    class ConfirmationLdsTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CONL";

        using GedcomTag::GedcomTag;
    };



    class CremationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CREM";

        using GedcomTag::GedcomTag;
    };



    class EngagementTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ENGA";

        using GedcomTag::GedcomTag;
    };



    class NaturalizationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NATU";

        using GedcomTag::GedcomTag;
    };



    class ProbateTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PROB";

        using GedcomTag::GedcomTag;
    };



    class RetirementTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "RETI";

        using GedcomTag::GedcomTag;
    };

}