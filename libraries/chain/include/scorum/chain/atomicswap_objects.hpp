#pragma once

#include <fc/fixed_string.hpp>

#include <scorum/protocol/authority.hpp>
#include <scorum/protocol/scorum_operations.hpp>

#include <scorum/chain/scorum_object_types.hpp>
#include <scorum/chain/witness_objects.hpp>
#include <scorum/chain/shared_authority.hpp>

#include <boost/multi_index/composite_key.hpp>

#include <numeric>

#include <scorum/protocol/atomicswap_helper.hpp>

namespace scorum {
namespace chain {

using scorum::protocol::asset;
using scorum::protocol::atomicswap::hash_index_type;

class atomicswap_contract_object : public object<atomicswap_contract_object_type, atomicswap_contract_object>
{
    atomicswap_contract_object() = delete;

public:
    template <typename Constructor, typename Allocator>
    atomicswap_contract_object(Constructor&& c, allocator<Allocator> a)
        : secret_hash(a)
        , secret(a)
    {
        c(*this);
    }

    id_type id;

    account_name_type owner;

    account_name_type to;
    asset amount = asset(0, SCORUM_SYMBOL);

    fc::shared_string secret_hash;
    fc::shared_string secret;
    hash_index_type contract_hash;

    bool wait_deadline_to_die = false;

    time_point_sec created = time_point_sec::min();
    time_point_sec deadline = time_point_sec::min();
};

struct by_owner_name;
struct by_contract_hash;

typedef multi_index_container<atomicswap_contract_object,
                              indexed_by<ordered_unique<tag<by_id>,
                                                        member<atomicswap_contract_object,
                                                               atomicswap_contract_id_type,
                                                               &atomicswap_contract_object::id>>,
                                         ordered_non_unique<tag<by_owner_name>,
                                                            member<atomicswap_contract_object,
                                                                   account_name_type,
                                                                   &atomicswap_contract_object::owner>>,
                                         ordered_unique<tag<by_contract_hash>,
                                                        member<atomicswap_contract_object,
                                                               hash_index_type,
                                                               &atomicswap_contract_object::contract_hash>>>,
                              allocator<atomicswap_contract_object>>
    atomicswap_contract_index;
}
}

FC_REFLECT(scorum::chain::atomicswap_contract_object,
           (id)(owner)(to)(amount)(secret_hash)(secret)(contract_hash)(wait_deadline_to_die)(created)(deadline))

CHAINBASE_SET_INDEX_TYPE(scorum::chain::atomicswap_contract_object, scorum::chain::atomicswap_contract_index)
