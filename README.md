# smashcast-php-client

A PHP 7.1 library for interfacing with the Smashcast.tv API.

## Installation

`composer require almostinteractive/smashcast-php-client`

## Usage Example

```php
$apiClient = new SmashcastApi('MY_APP_NAME', 'MY_APP_TOKEN', 'MY_APP_SECRET');

$state = 'some data';
$authUrl = $apiClient->getOauthApi()->getAuthUrl(true, $state);


$accessToken = $apiClient->getOauthApi()->getUserAccessToken($code, 'http://localhost/callback.php');

$username = $apiClient->getUsersApi()->getUserByAccessToken($accessToken);
$userInfo = $apiClient->getUsersApi()->getUserInfo($username, $accessToken);
```

## Notes from the Author
I plan on only adding the endpoints as I need them. Pull requests welcome. Requests will be duly considered.
