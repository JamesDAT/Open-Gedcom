// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include "GedcomObject.h"
#include "OpenGedcom/Tags/SourcesCitations.h"

#include <tuple>

namespace OpenGedcom {

    // register the builtin types defined in GedcomObject.h
    using BuiltinTags = std::tuple<

        /// Records
        HeadTag,
        TrailerTag,
        IndiTag,
        FamilyTag,
        SourceTag,
        RepoTag,
        SubmitterTag,
        ObjectTag,
        SharedNoteTag,

        /// Identity & Linking
        UIDTag,
        RefTag,
        ExternalIdTag,
        NameTag,
        NamePrefixTag,
        GivenNamesTag,
        SurnameTag,
        TypeTag,

        /// Events
        BirthTag,
        DeathTag,
        MarriageTag,
        BurriedTag,
        EventTag,
        OrdinationTag,
        ImmigrationTag,
        EmigrationTag,
        WillTag,
        AdoptionTag,
        BaptismTag,
        BarMitzvahTag,
        BasMitzvahTag,
        BlessingTag,
        AdultChristeningTag,
        ChristeningTag,
        ConfirmationTag,
        ConfirmationLdsTag,
        CremationTag,
        EngagementTag,
        NaturalizationTag,
        ProbateTag,
        RetirementTag,


        /// Dates
        DateTag,
        SortDateTag,
        TimeTag,
        PhraseTag,

        /// Places & Addresses
        PlaceTag,
        FormatTag,
        AddressTag,
        CountryTag,
        StateTag,
        CityTag,
        PostTag,

        /// Sources & Citations
        PageTag,
        CallTag,
        DataTag,
        AgencyTag,
        TitleTag,
        AbbreviationTag,
        AuthorTag,
        PublicationTag,

        /// Attributes & Facts
        FactTag,
        OccupationTag,
        CasteTag,
        SexTag,
        RoleTag,
        StatusTag,
        ResidanceTag,
        NationalityTag,
        NumChildrenTag,
        NumMarriagesTag,
        DescriptionTag,
        EducationTag,
        NationalIdTag,
        PropertyTag,
        ReligionTag,
        SSNTag,
        

        /// Communications & Contacts
        PhoneTag,
        EmailTag,
        WebsiteTag,
        FaxTag,

        /// Multimedia
        FileTag,
        MediaTag,
        WidthTag,
        HeightTag,
        LeftTag,
        TopTag,

        /// Notes & Text
        TextTag,
        NoteTag,
        TranslationTag,
        ChangeTag,

        /// Header Metadata
        GedcTag,
        SourceTag,
        LanguageTag,
        SchemaTag,
        VersionTag,
        CharacterTag,
        CorporateTag,
        CopyrightTag,

        /// Family & Relationships
        FamilyChildTag,
        FamilySpouseTag,
        HusbandTag,
        WifeTag,
        ChildTag,
        PedigreeTag
    >;
}