#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/asset.hpp>
#include <string>
using namespace eosio;

using std::string;
class hacksf : public eosio::contract {
private:
    static const uint64_t symbol = N(EOS);
    bool isnewuser( account_name user ) {
      hacktable obj(_self, _self);
      // get object by secondary key
      auto hacks = obj.get_index<N(getbyuser)>();
      auto hack = hacks.find(user);

      return hack == hacks.end();
    }
     bool userexists( account_name user ) {
      hacktable obj(_self, _self);
      // get object by secordary key
      auto hacks = obj.get_index<N(getbyuser)>();
      auto hack = hacks.find(user);

      return hack == hacks.end();
    }

      /// @abi action 
    void get(const account_name _user) {
        hacktable obj(_self, _self);
        auto notes = obj.get_index<N(getbyuser)>();
        auto iterator = notes.find(_user);
        eosio_assert(iterator != notes.end(), "Account not found");
        auto currentData = notes.get(_user);
    print("Key: ", currentData.prim_key);
    }

    /// @abi table
    struct hackstruct {
      // CANNOT CHANGE STRUCT ONCE CONTRACT IS DEPLOYED
      uint64_t      prim_key;  // primary key
      account_name  user;      // account name for the user
      std::string   party;      // username
      std::string   dob;
      std::string   gender;
      uint64_t      height; //in cm
      uint64_t      timestamp; // the store the last update block time

      // primary key
      auto primary_key() const { return prim_key; }
      // secondary key: user
      account_name get_by_user() const { return user; }
    };

    // create a multi-index table and support secondary key
    typedef eosio::multi_index< N(hackstruct), hackstruct,
      indexed_by< N(getbyuser), const_mem_fun<hackstruct, account_name, &hackstruct::get_by_user> >
      > hacktable;

      /// @abi table
    struct appstruct {
      uint64_t      prim_key;  // primary key
      account_name  user;      // account name for the user
      std::string   app_name;      // app name
      uint64_t      app_id;
      std::string   url;
      std::string   permissions; //permissions required by app in string
      uint64_t      timestamp; // the store the last update block time

      // primary key
      auto primary_key() const { return prim_key; }
      // secondary key: user
      account_name get_by_user() const { return user; }
    };

    // create a multi-index table and support secondary key
    typedef eosio::multi_index< N(appstruct), appstruct,
      indexed_by< N(getbyuser), const_mem_fun<appstruct, account_name, &appstruct::get_by_user> >
      > apptable;

     

    /// @abi action
    /*void send_receipt(account_name buyer, std::string message){
      action(
        permission_level{get_self(), N(active)},
        get_self(),
        N(receipt),
        std::make_tuple(buyer, message)
      ).send();
    }*/

  public:
    using contract::contract;

     /// @abi action

     void addapp(const account_name _user,  std::string _appname, uint64_t _appid, std::string _url, std::string _permissions) {
        
        //usernames are actually numbers under the account name
        require_auth(_user);
       apptable obj(_self, _self);
        auto notes = obj.get_index<N(getbyuser)>();
        auto iterator = notes.find(_user);
        //eosio_assert(iterator != notes.end(), "User not found");
        
        

 obj.emplace( _self, [&]( auto& address ) {
          address.prim_key    = obj.available_primary_key();
          address.user        = _user;
          address.app_name        = _appname;
          address.app_id        = _appid;
          address.url        = _url;
          address.permissions        = _permissions;
          address.timestamp   = now();
        });

       
    }

    /// @abi action
    void add(const account_name _user,  std::string enc_photohash) {
        
        //usernames are actually numbers under the account name
        require_auth(_user);
       hacktable obj(_self, _self);
        auto notes = obj.get_index<N(getbyuser)>();
        auto iterator = notes.find(_user);
        //eosio_assert(iterator != notes.end(), "User not found");
        
        

 obj.emplace( _self, [&]( auto& address ) {
          address.prim_key    = obj.available_primary_key();
          address.user        = _user;
          address.party        = enc_photohash;
          address.timestamp   = now();
        });

       
      }
      


    /// @abi action

     /*void deposit(account_name buyer, account_name seller, eosio::asset quantity, std::string memo) {

      

      balance_table balance(_self, buyer);
      auto hodl_it = balance.find(symbol);

      asset new_balance;
      if(hodl_it != balance.end())
        balance.modify(hodl_it, buyer, [&](auto& row){
            row.funds -= quantity;
            new_balance = row.funds;
        });
      else
        balance.emplace(buyer, [&](auto& row){
            row.funds = quantity;
            new_balance  = row.funds;
        });

      // std::string message = name{buyer}.to_string() + " deposited " + quantity.amount + ", now has a total of " + new_balance;
      send_receipt(buyer, "You deposited some EOS.");
    }
*/

    /// @abi action
    void buydata(account_name _buyer, account_name _seller, std::string _hash, uint64_t price) 
    {
       
    }
    

};

// specify the contract name, and export a public action: update
EOSIO_ABI( hacksf, (addapp) (add) (buydata))
