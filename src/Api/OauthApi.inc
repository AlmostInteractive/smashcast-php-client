<?php

declare(strict_types=1);

namespace SmashcastApi\Api;

use GuzzleHttp\Client;
use GuzzleHttp\Exception\GuzzleException;

class OauthApi extends AbstractApiBase
{
    private const AUTH_ENDPOINT = 'https://api.smashcast.tv/oauth/login';

    private $appSecret;

    public function __construct(string $appName, string $appToken, string $appSecret, Client $guzzleClient)
    {
        parent::__construct($appName, $appToken, $guzzleClient);
        $this->appSecret = $appSecret;
    }

    /**
     * @return string A full authentication URL, including the Guzzle client's base URI.
     */
    public function getAuthUrl(bool $forceVerify = false, ?string $state = null): string
    {
        return sprintf(
            '%s%s',
            self::AUTH_ENDPOINT,
            $this->getPartialAuthUrl($forceVerify, $state)
        );
    }

    /**
     * @throws GuzzleException
     */
    public function getUserAccessToken(string $requestToken): ?string
    {
        $hash = base64_encode($this->appToken . $this->appSecret);

        $response = $this->apiPost('oauth/exchange',
            [
                'request_token' => $requestToken,
                'app_token' => $this->appToken,
                'hash' => $hash
            ]);

        $token = json_decode($response->getBody()->getContents(), true);
        return $token['access_token'] ?? null;
    }

    /**
     * @throws GuzzleException
     * @deprecated This does not seem to ever work; perhaps the api documentation is bad
     */
    public function isValidAccessToken(string $accessToken): bool
    {
        $response = $this->apiGet(
            'auth/valid/' . $this->appName,
            ['token' => $accessToken]
        );
        $data = json_decode($response->getBody()->getContents(), true);
        return $data['success'] === true;
    }

    /**
     * @return string A partial authentication URL, excluding the Guzzle client's base URI.
     */
    private function getPartialAuthUrl(bool $forceVerify = false, ?string $state = null): string
    {
        $optionalParameters = '';
        $optionalParameters .= $forceVerify ? '&force_auth=force' : '';
        $optionalParameters .= $state ? sprintf('&state=%s', $state) : '';

        return sprintf(
            '?app_token=%s%s',
            $this->appToken,
            $optionalParameters
        );
    }
}
