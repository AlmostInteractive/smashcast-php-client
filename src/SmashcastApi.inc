<?php

/*
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 *
 * https://github.com/AlmostInteractive/smashcast-php-client
 */

declare(strict_types=1);

namespace SmashcastApi;

use GuzzleHttp\Client;
use SmashcastApi\Api\ChannelsApi;
use SmashcastApi\Api\OauthApi;
use SmashcastApi\Api\UsersApi;


class SmashcastApi
{
    private $oauthApi;
    private $usersApi;
    private $channelsApi;

    public function __construct(string $appName, string $appToken, string $appSecret, Client $guzzleClient = null)
    {
        $guzzleClient = $guzzleClient ?? new SmashcastGuzzleClient();

        $this->oauthApi = new OauthApi($appName, $appToken, $appSecret, $guzzleClient);
        $this->usersApi = new UsersApi($appName, $appToken, $guzzleClient);
        $this->channelsApi = new ChannelsApi($appName, $appToken, $guzzleClient);
    }

    public function getOauthApi(): OauthApi { return $this->oauthApi; }

    public function getUsersApi(): UsersApi { return $this->usersApi; }

    public function getChannelsApi(): ChannelsApi { return $this->channelsApi; }
}

