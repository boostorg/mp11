module;

#include <cassert>

export module boost.mp11;
import std;

#define BOOST_MP11_INTERFACE_UNIT
#define BOOST_COMPATIBILITY_HEADERS_SKIP_IMPORT

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif

extern "C++" {
#include <boost/mp11.hpp>
}

export namespace boost::mp11 {

// algorithm
using mp11::mp_transform;
using mp11::mp_transform_q;
using mp11::mp_transform_if;
using mp11::mp_transform_if_q;
using mp11::mp_filter;
using mp11::mp_filter_q;
using mp11::mp_fill;
using mp11::mp_contains;
using mp11::mp_repeat_c;
using mp11::mp_repeat;
using mp11::mp_product;
using mp11::mp_product_q;
using mp11::mp_drop_c;
using mp11::mp_drop;
using mp11::mp_from_sequence;
using mp11::mp_iota_c;
using mp11::mp_iota;
using mp11::mp_at_c;
using mp11::mp_at;
using mp11::mp_take_c;
using mp11::mp_take;
using mp11::mp_slice_c;
using mp11::mp_slice;
using mp11::mp_back;
using mp11::mp_pop_back;
using mp11::mp_replace;
using mp11::mp_replace_if;
using mp11::mp_replace_if_q;
using mp11::mp_remove;
using mp11::mp_flatten;
using mp11::mp_partition;
using mp11::mp_partition_q;
using mp11::mp_sort;
using mp11::mp_sort_q;
using mp11::mp_nth_element_c;
using mp11::mp_nth_element;
using mp11::mp_nth_element_q;
using mp11::mp_find;
using mp11::mp_find_if;
using mp11::mp_find_if_q;
using mp11::mp_reverse;
using mp11::mp_reverse_fold;
using mp11::mp_reverse_fold_q;
using mp11::mp_unique;
using mp11::mp_unique_if;
using mp11::mp_unique_if_q;
using mp11::mp_all_of;
using mp11::mp_all_of_q;
using mp11::mp_none_of;
using mp11::mp_none_of_q;
using mp11::mp_any_of;
using mp11::mp_any_of_q;
using mp11::mp_replace_at;
using mp11::mp_replace_at_c;
using mp11::mp_for_each;
using mp11::mp_insert;
using mp11::mp_insert_c;
using mp11::mp_erase;
using mp11::mp_erase_c;
using mp11::mp_starts_with;
using mp11::mp_rotate_left_c;
using mp11::mp_rotate_left;
using mp11::mp_rotate_right_c;
using mp11::mp_rotate_right;
using mp11::mp_power_set;
using mp11::mp_partial_sum;
using mp11::mp_partial_sum_q;
using mp11::mp_iterate;
using mp11::mp_iterate_q;
using mp11::mp_pairwise_fold_q;
using mp11::mp_pairwise_fold;
using mp11::mp_sliding_fold_q;
using mp11::mp_sliding_fold;
using mp11::mp_intersperse;
using mp11::mp_split;
using mp11::mp_join;

// bind
using mp11::mp_bind_front;
using mp11::mp_bind_front_q;
using mp11::mp_bind_back;
using mp11::mp_bind_back_q;
using mp11::mp_arg;
using mp11::_1;
using mp11::_2;
using mp11::_3;
using mp11::_4;
using mp11::_5;
using mp11::_6;
using mp11::_7;
using mp11::_8;
using mp11::_9;
using mp11::mp_bind;
using mp11::mp_bind_q;

// function
using mp11::mp_and;
using mp11::mp_all;
using mp11::mp_or;
using mp11::mp_any;
using mp11::mp_same;
using mp11::mp_similar;
using mp11::mp_less;
using mp11::mp_min;
using mp11::mp_max;

// integer_sequence
using mp11::integer_sequence;
using mp11::make_integer_sequence;
using mp11::make_integer_sequence;
using mp11::index_sequence;
using mp11::make_index_sequence;
using mp11::index_sequence_for;

// integral
using mp11::mp_bool;
using mp11::mp_true;
using mp11::mp_false;
using mp11::mp_to_bool;
using mp11::mp_not;
using mp11::mp_int;
using mp11::mp_size_t;

// lambda
using mp11::mp_lambda;

// list
using mp11::mp_list_c;
using mp11::mp_size;
using mp11::mp_empty;
using mp11::mp_assign;
using mp11::mp_clear;
using mp11::mp_pop_front;
using mp11::mp_first;
using mp11::mp_rest;
using mp11::mp_second;
using mp11::mp_third;
using mp11::mp_push_front;
using mp11::mp_push_back;
using mp11::mp_rename_v;
using mp11::mp_replace_front;
using mp11::mp_replace_first;
using mp11::mp_replace_second;
using mp11::mp_replace_third;
using mp11::mp_transform_front;
using mp11::mp_transform_front_q;
using mp11::mp_transform_first;
using mp11::mp_transform_first_q;
using mp11::mp_transform_second;
using mp11::mp_transform_second_q;
using mp11::mp_transform_third;
using mp11::mp_transform_third_q;

// map
using mp11::mp_map_contains;
using mp11::mp_map_insert;
using mp11::mp_map_replace;
using mp11::mp_map_update;
using mp11::mp_map_update_q;
using mp11::mp_map_erase;
using mp11::mp_map_keys;
using mp11::mp_is_map;

// set
using mp11::mp_set_contains;
using mp11::mp_set_push_back;
using mp11::mp_set_push_front;
using mp11::mp_is_set;
using mp11::mp_set_union;
using mp11::mp_set_intersection;
using mp11::mp_set_difference;

// tuple
using mp11::tuple_apply;
using mp11::construct_from_tuple;
using mp11::tuple_for_each;
using mp11::tuple_transform;

// utility
using mp11::mp_identity;
using mp11::mp_identity_t;
using mp11::mp_inherit;
using mp11::mp_eval_if_c;
using mp11::mp_eval_if;
using mp11::mp_eval_if_q;
using mp11::mp_eval_if_not;
using mp11::mp_eval_if_not_q;
using mp11::mp_eval_or;
using mp11::mp_eval_or_q;
using mp11::mp_valid_and_true;
using mp11::mp_valid_and_true_q;
using mp11::mp_cond;
using mp11::mp_quote;
using mp11::mp_quote_trait;
using mp11::mp_invoke_q;
using mp11::mp_not_fn;
using mp11::mp_not_fn_q;
using mp11::mp_compose;
using mp11::mp_compose_q;

// other
using mp11::mp_list_v;
using mp11::mp_count;
using mp11::mp_count_if;
using mp11::mp_count_if_q;
using mp11::mp_fold;
using mp11::mp_fold_q;
using mp11::mp_copy_if;
using mp11::mp_copy_if_q;
using mp11::mp_with_index;
using mp11::mp_with_index;
using mp11::mp_append;
using mp11::mp_min_element;
using mp11::mp_min_element_q;
using mp11::mp_max_element;
using mp11::mp_max_element_q;
using mp11::mp_is_value_list;
using mp11::mp_is_list;
using mp11::mp_plus;
using mp11::mp_if_c;
using mp11::mp_if;
using mp11::mp_valid;
using mp11::mp_valid_q;
using mp11::mp_defer;
using mp11::mp_rename;
using mp11::mp_apply;
using mp11::mp_apply_q;
using mp11::mp_list;
using mp11::mp_value;
using mp11::mp_map_find;
using mp11::mp_void;
using mp11::mp_remove_if;
using mp11::mp_remove_if_q;
using mp11::mp_front;

}
