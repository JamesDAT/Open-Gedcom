// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class BirthTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BIRT";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class DeathTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "DEAT";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class MarriageTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "MARR";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class BurriedTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BURI";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class EventTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EVEN";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class OrdinationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ORDN";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class ImmigrationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "IMMI";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class EmigrationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EMIG";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class WillTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "WILL";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class AdoptionTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ADOP";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class BaptismTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BAPM";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class BarMitzvahTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BARM";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class BasMitzvahTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BASM";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class BlessingTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "BLES";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class AdultChristeningTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHRA";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class ChristeningTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHR";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class ConfirmationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CONF";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class ConfirmationLdsTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CONL";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class CremationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CREM";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class EngagementTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ENGA";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class NaturalizationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NATU";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class ProbateTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PROB";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };



    class RetirementTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "RETI";
        static constexpr TagTraits Traits = TagTraits::Event;

        using GedcomTag::GedcomTag;
    };

}