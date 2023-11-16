// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract EVotingSystem {
    struct Voter {
        bool isRegistered;
        bool hasVoted;
        uint8 votedPartyId;
    }

    struct Party {
        string name;
        uint256 voteCount;
    }

    address public admin;
    Party[] public parties;
    mapping(string => Voter) public voters;

    event VoterRegistered(string voterId);
    event PartyAdded(uint256 partyId, string partyName);
    event Voted(string voterId, uint256 partyId);

    constructor() {
        admin = msg.sender;
    }

    modifier onlyAdmin() {
        require(msg.sender == admin, "Only admin can perform this operation");
        _;
    }

    modifier onlyRegisteredVoter(string memory _voterId) {
        require(voters[_voterId].isRegistered, "Voter is not registered");
        _;
    }

    modifier hasNotVoted(string memory _voterId) {
        require(!voters[_voterId].hasVoted, "Voter has already voted");
        _;
    }

    function addVoter(string memory _voterId) public onlyAdmin {
        require(!voters[_voterId].isRegistered, "Voter already registered");
        voters[_voterId].isRegistered = true;
        emit VoterRegistered(_voterId);
    }

    function addParty(string memory _name) public onlyAdmin {
        uint256 partyId = parties.length;
        parties.push(Party(_name, 0));
        emit PartyAdded(partyId, _name);
    }

    function loginAndVote(string memory _voterId, uint256 _partyId) public onlyRegisteredVoter(_voterId) hasNotVoted(_voterId) {
        require(_partyId < parties.length, "Invalid party ID");
        voters[_voterId].hasVoted = true;
        voters[_voterId].votedPartyId = uint8(_partyId);
        parties[_partyId].voteCount++;
        emit Voted(_voterId, _partyId);
    }

    function getVoteCount(uint256 _partyId) public view returns (uint256) {
        require(_partyId < parties.length, "Invalid party ID");
        return parties[_partyId].voteCount;
    }

    function getPartyCount() public view returns (uint256) {
        return parties.length;
    }
}